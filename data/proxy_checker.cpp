#include "proxy_checker.h"

using namespace Data;

ProxyChecker::ProxyChecker(QObject *parent)
    :   QThread(parent)
        ,m_ProxyList()
        ,m_InfiniteLoop(false)
        ,m_SimultaneousCount(1)
        ,m_pNetworkAccessMgr(nullptr)
        ,m_CurrentRun(0)
{
    connect(this, SIGNAL(started()), SLOT(onThread_started()));
    connect(this, SIGNAL(finished()), SLOT(onThread_finished()));
}

ProxyChecker::~ProxyChecker(){}

bool
ProxyChecker::addProxy(const Proxy& proxy)
{
    if(!m_ProxyList.contains(proxy)){
        ProxyTestInfo pti;
        pti._Proxy = proxy;
        m_ProxyList.append(proxy);

        ProxyTestInfo* ourPti = findProxy(proxy.Id());
        if(ourPti != nullptr)
            connect(&(ourPti->_Proxy), SIGNAL(statusChanged(ProxyStatus)), SLOT(onProxy_statusChanged(ProxyStatus)));

        return true;
    }

    return false;
}

bool
ProxyChecker::remProxy(const QUuid& proxyId)
{
    Proxy tempProxy(proxyId);
    if(m_ProxyList.contains(tempProxy)){
        m_ProxyList.removeOne(tempProxy);
        return true;
    }

    return false;
}

void
ProxyChecker::clearProxies()
{
    m_ProxyList.clear();
}

void
ProxyChecker::testAllProxiesAtOnce()
{
    testProxiesInChunksOf(m_ProxyList.size());
}

void
ProxyChecker::testNextProxy()
{
    ProxyChecker::ProxyTestInfo* proxy = findNextProxy();

    if(proxy == nullptr)
        return;

    QNetworkProxy qProxy;
    qProxy.setHostName(proxy->_Proxy.Address());
    qProxy.setPort(proxy->_Proxy.Port());
    qProxy.setUser(proxy->_Proxy.UserName());
    qProxy.setType(QNetworkProxy::ProxyType::HttpProxy);
    qProxy.setCapabilities(QNetworkProxy::Capability::TunnelingCapability);
    m_pNetworkAccessMgr->setProxy(qProxy);

    QNetworkRequest request(QUrl(proxy->_Proxy.TestUrl()));
    request.setRawHeader("User-Agent", DEFAULT_BROWSER_AGENT);

    QNetworkReply* pReply = m_pNetworkAccessMgr->get(request);
    pReply->ignoreSslErrors();
    if(pReply == nullptr)
        return;

    if(pReply != nullptr){
        proxy->_pReply = pReply;
        proxy->_RunId = m_CurrentRun;

        connect(pReply, SIGNAL(aboutToClose()), SLOT(onRequest_aboutToClose()));
        connect(pReply, SIGNAL(bytesWritten(qint64)), SLOT(onRequest_bytesWritten(qint64)));
        connect(pReply, SIGNAL(channelBytesWritten(int,qint64)), SLOT(onRequest_channelBytesWritten(int,qint64)));
        connect(pReply, SIGNAL(channelReadyRead(int)), SLOT(onRequest_channelReadyRead(int)));
        connect(pReply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(onRequest_downloadProgress(qint64,qint64)));
        connect(pReply, SIGNAL(encrypted()), SLOT(onRequest_encrypted()));
        connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onRequest_error(QNetworkReply::NetworkError)));
        connect(pReply, SIGNAL(finished()), SLOT(onRequest_finished()));
        connect(pReply, SIGNAL(metaDataChanged()), SLOT(onRequest_metaDataChanged()));
        connect(pReply, SIGNAL(preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator*)), SLOT(onRequest_preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator*)));
        connect(pReply, SIGNAL(readChannelFinished()), SLOT(onRequest_readChannelFinished()));
        connect(pReply, SIGNAL(readyRead()), SLOT(onRequest_readyRead()));
        connect(pReply, SIGNAL(redirected(QUrl)), SLOT(onRequest_redirected(QUrl)));
        connect(pReply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(onRequest_sslErrors(QList<QSslError>)));
        connect(pReply, SIGNAL(uploadProgress(qint64,qint64)), SLOT(onRequest_uploadProgress(qint64,qint64)));
        connect(pReply, SIGNAL(destroyed(QObject*)), SLOT(onRequest_destroyed(QObject*)));

        proxy->_Proxy.setLastStatus(Data::ProxyStatus::Testing);
        connect(proxy->_Proxy.TimeoutTimer(), SIGNAL(timeout()), pReply, SLOT(abort()));
        proxy->_Proxy.TimeoutTimer()->start();
    }
}

void
ProxyChecker::testProxiesInChunksOf(int chunkSize)
{
    // Blocking the signals so that no "onRequest_finished()" is triggered before starting to process the next chunk of proxies
    blockSignals(true);
    for(int i = 0; i < chunkSize; i++)
        testNextProxy();
    blockSignals(false);
}

ProxyChecker::ProxyTestInfo*
ProxyChecker::findProxy(QNetworkReply* reply)
{
    ProxyTestInfo* proxy = nullptr;

    if(reply == nullptr)
        return proxy;

    QList<ProxyTestInfo>::iterator iter;
    for(iter = m_ProxyList.begin(); iter != m_ProxyList.end(); iter++){
        if((*iter)._pReply == reply){
            proxy = &(*iter);
            break;
        }
    }

    return proxy;
}

ProxyChecker::ProxyTestInfo*
ProxyChecker::findProxy(const QUuid& id)
{
    ProxyTestInfo* proxy = nullptr;

    QList<ProxyTestInfo>::iterator iter;
    for(iter = m_ProxyList.begin(); iter != m_ProxyList.end(); iter++){
        if((*iter)._Proxy.Id() == id){
            proxy = &(*iter);
            break;
        }
    }

    return proxy;
}

ProxyChecker::ProxyTestInfo*
ProxyChecker::findNextProxy()
{
    ProxyChecker::ProxyTestInfo*  pti = nullptr;

    for(ProxyChecker::ProxyTestInfo& element : m_ProxyList){
        if(element._RunId < m_CurrentRun && element._pReply == nullptr){
            pti = &element;
            break;
        }
    }

    return pti;
}

int
ProxyChecker::activeTests()const
{
    int result = 0;

    for(const ProxyChecker::ProxyTestInfo& element : m_ProxyList){
        if(element._pReply != nullptr)
            result++;
    }

    return result;
}

void
ProxyChecker::printDebugProxyData(QNetworkReply* pReply)
{
    if(pReply == nullptr)
        return;

    ProxyChecker::ProxyTestInfo* proxy = findProxy(pReply);
    if(proxy != nullptr)
        proxy->_Proxy.printStatus();
}

void
ProxyChecker::newRun()
{
    // Clear cache
    QAbstractNetworkCache* cache = m_pNetworkAccessMgr->cache();
    if(cache != nullptr)
        cache->clear();

    switch(m_SimultaneousCount)
    {
    case -1:
        testAllProxiesAtOnce();
        break;
    default:
        testProxiesInChunksOf(m_SimultaneousCount);
        break;
    }
}

void
ProxyChecker::onNetwork_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)
    Q_UNUSED(reply)

//    PRINT_LOCATION;
//    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply)
//    PRINT_LOCATION;
//    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_finished(QNetworkReply *reply)
{
    Q_UNUSED(reply)
//    PRINT_LOCATION;
//    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    Q_UNUSED(accessible)
//    PRINT_LOCATION << " -> " << accessible;
}

void
ProxyChecker::onNetwork_networkSessionConnected()
{
//    PRINT_LOCATION;
}

void
ProxyChecker::onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)
    Q_UNUSED(reply)

//    PRINT_LOCATION;
//    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)
    Q_UNUSED(proxy)

//    PRINT_LOCATION << "\n\t\t" << proxy.hostName() << ":" << proxy.port();
}

void
ProxyChecker::onNetwork_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply)
    Q_UNUSED(errors)

//    PRINT_LOCATION;
//    printDebugProxyData(reply);

    foreach(const QSslError& error, errors)
        qDebug() << "\t\tSSL error: " << error.errorString();
}

void
ProxyChecker::onRequest_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    Q_UNUSED(bytesReceived)
    Q_UNUSED(bytesTotal)

//    PRINT_LOCATION << "\n\t\t" << bytesReceived << " out of " << bytesTotal;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_error(QNetworkReply::NetworkError code)
{
    Q_UNUSED(code)

//    QNetworkReply* pReply = qobject_cast<QNetworkReply*>(sender());

//    PRINT_LOCATION  << "\n\t\tcode: " << code << ": " << pReply->errorString();
//    printDebugProxyData(pReply);
}

void
ProxyChecker::onRequest_finished()
{
//    PRINT_LOCATION;

    QNetworkReply* pReply = qobject_cast<QNetworkReply*>(sender());
//    printDebugProxyData(pReply);

    ProxyChecker::ProxyTestInfo* proxy = findProxy(pReply);
    if(proxy != nullptr){

        if(proxy->_pReply != nullptr){
            proxy->_pReply->deleteLater();
            proxy->_pReply = nullptr;
        }

        // Update the status
        switch(pReply->error())
        {
        case QNetworkReply::NetworkError::NoError:
            proxy->_Proxy.setLastStatus(Data::ProxyStatus::Active);
            proxy->_Proxy.setLastStatusDescription("No error");
            break;
        default:
            proxy->_Proxy.setLastStatus(Data::ProxyStatus::Inactive);
            proxy->_Proxy.setLastStatusDescription(pReply->errorString());
            break;
        }


        proxy->_Proxy.setLastCheck(QDateTime::currentDateTime());

        ProxyChecker::ProxyTestInfo* nextProxyTest = findNextProxy();
        if(nextProxyTest == nullptr){
            // We are at the end of the list
            if(activeTests() == 0){
                m_CurrentRun++;
                msleep(DEFAULT_SLEEP_BETWEEN_RUNS);
                newRun();
            }
        }else{
            testNextProxy();
        }
    }
}

void
ProxyChecker::onRequest_metaDataChanged()
{
//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_sslErrors(const QList<QSslError> & errors)
{
//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));

    foreach(const QSslError& error, errors)
        qDebug() << "\t\tSSL error: " << error.errorString();
}

void
ProxyChecker::onRequest_preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)

//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_redirected(const QUrl &url)
{
    Q_UNUSED(url)

//    PRINT_LOCATION << "\n\t\t" << url.toString();
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    Q_UNUSED(bytesSent)
    Q_UNUSED(bytesTotal)

//    PRINT_LOCATION << "\n\t\t" << bytesSent << " out of " << bytesTotal;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_encrypted()
{
//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_destroyed(QObject* obj)
{
    Q_UNUSED(obj)

//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(obj));
}

void
ProxyChecker::onRequest_aboutToClose()
{
//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_bytesWritten(qint64 bytes)
{
    Q_UNUSED(bytes)

//    PRINT_LOCATION << "\n\t\t" << bytes;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_channelBytesWritten(int channel, qint64 bytes)
{
    Q_UNUSED(channel)
    Q_UNUSED(bytes)

//    PRINT_LOCATION << "\n\t\t" << "channel: " << channel << "; bytes: " << bytes;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_channelReadyRead(int channel)
{
    Q_UNUSED(channel)

//    PRINT_LOCATION << "\n\t\t" << "channel: " << channel;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_readChannelFinished()
{
//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_readyRead()
{
//    PRINT_LOCATION;
//    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onProxy_statusChanged(ProxyStatus newStatus)
{
    Proxy* proxy = qobject_cast<Proxy*>(sender());
    if(proxy != nullptr){
        proxy->printStatus();
        emit proxyStatusChanged(qobject_cast<Proxy*>(sender()), newStatus);
    }
}

void
ProxyChecker::onThread_started()
{
//    PRINT_LOCATION;

    QNetworkProxyFactory::setUseSystemConfiguration(false);

    if(m_pNetworkAccessMgr == nullptr)
    {
        m_pNetworkAccessMgr = new QNetworkAccessManager();

        connect(m_pNetworkAccessMgr, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(onNetwork_authenticationRequired(QNetworkReply*,QAuthenticator*)));
        connect(m_pNetworkAccessMgr, SIGNAL(encrypted(QNetworkReply*)), SLOT(onNetwork_encrypted(QNetworkReply*)));
        connect(m_pNetworkAccessMgr, SIGNAL(finished(QNetworkReply*)), SLOT(onNetwork_finished(QNetworkReply*)));
        connect(m_pNetworkAccessMgr, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), SLOT(onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
        connect(m_pNetworkAccessMgr, SIGNAL(networkSessionConnected()), SLOT(onNetwork_networkSessionConnected()));
        connect(m_pNetworkAccessMgr, SIGNAL(preSharedKeyAuthenticationRequired(QNetworkReply*,QSslPreSharedKeyAuthenticator*)), SLOT(onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply*,QSslPreSharedKeyAuthenticator*)));
        connect(m_pNetworkAccessMgr, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)), SLOT(onNetwork_proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)));
        connect(m_pNetworkAccessMgr, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), SLOT(onNetwork_sslErrors(QNetworkReply*,QList<QSslError>)));
    }

    // Restart counting
    m_CurrentRun = 1;
    for(ProxyChecker::ProxyTestInfo& p : m_ProxyList){
        p._RunId = 0;
        if(p._pReply != nullptr){
            p._pReply->deleteLater();
            p._pReply = nullptr;
        }
    }

    newRun();
}

void
ProxyChecker::onThread_finished()
{
//    PRINT_LOCATION;
}
