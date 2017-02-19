#include "proxy_checker.h"

using namespace Data;

ProxyChecker::ProxyChecker(QObject *parent)
    :   QThread(parent)
        ,m_ProxyList()
        ,m_InfiniteLoop(false)
        ,m_SimultaneousCount(1)
        ,m_pNetworkAccessMgr(nullptr)
{
    connect(this, SIGNAL(started()), SLOT(onThread_started()));
    connect(this, SIGNAL(finished()), SLOT(onThread_finished()));
}

ProxyChecker::~ProxyChecker(){}

void
ProxyChecker::run()
{
    exec();
}

bool
ProxyChecker::addProxy(const Proxy& proxy)
{
    if(!m_ProxyList.contains(proxy)){
        m_ProxyList.append(proxy);
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
    foreach (const Proxy& proxy, m_ProxyList) {
        if(proxy.Id().isNull())
            continue;

        if(!proxy.isValid())
            continue;

        QNetworkProxy qProxy;
        qProxy.setHostName(proxy.Address());
        qProxy.setPort(proxy.Port());
        qProxy.setUser(proxy.UserName());
        qProxy.setType(QNetworkProxy::ProxyType::HttpProxy);
        m_pNetworkAccessMgr->setProxy(qProxy);

        QNetworkProxy actualProxy = m_pNetworkAccessMgr->proxy();
        qDebug() << "Actual proxy info: " << actualProxy.hostName() << ":" << actualProxy.port();

        QNetworkRequest request(QUrl(proxy.TestUrl()));
        QNetworkReply* pReply = m_pNetworkAccessMgr->get(request);
        pReply->moveToThread(this->currentThread());

        if(pReply != nullptr){
            // We'll make a little not so cute cast...
            const_cast<Proxy*>(&proxy)->setTestReply(pReply);

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
        }
    }
}

void
ProxyChecker::testProxiesOneByOne()
{
}

void
ProxyChecker::testProxiesInChunksOf(int chunkSize)
{
    Q_UNUSED(chunkSize)
}

Data::Proxy*
ProxyChecker::findProxy(QNetworkReply* reply)
{
    Data::Proxy* proxy = nullptr;

    if(reply == nullptr)
        return proxy;

    QList<Proxy>::iterator iter;
    for(iter = m_ProxyList.begin(); iter != m_ProxyList.end(); iter++){
        if((*iter).TestReply() == reply){
            proxy = &(*iter);
            break;
        }
    }

    return proxy;
}

void
ProxyChecker::printDebugProxyData(QNetworkReply* pReply)
{
    if(pReply == nullptr)
        return;

    Proxy* proxy = findProxy(pReply);
    if(proxy != nullptr)
        qDebug() << "\t\t" << (pReply == nullptr ? "empty" : pReply->request().url().toString()) << " with proxy: " << proxy->Address() << ":" << proxy->Port();
}

void
ProxyChecker::onNetwork_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)

    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_encrypted(QNetworkReply *reply)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_finished(QNetworkReply *reply)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__ << " -> " << accessible;
}

void
ProxyChecker::onNetwork_networkSessionConnected()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
}

void
ProxyChecker::onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)

    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(reply);
}

void
ProxyChecker::onNetwork_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)

    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug() << "\t\t" << proxy.hostName() << ":" << proxy.port();
}

void
ProxyChecker::onNetwork_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;

    printDebugProxyData(reply);
    foreach(const QSslError& error, errors)
        qDebug() << "\t\tSSL error: " << error.errorString();
}

void
ProxyChecker::onRequest_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug() << "\t\t" << bytesReceived << " out of " << bytesTotal;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_error(QNetworkReply::NetworkError code)
{
    qDebug() << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;

    QNetworkReply* pReply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "\t\tcode: " << code << ": " << pReply->errorString();

    printDebugProxyData(pReply);
}

void
ProxyChecker::onRequest_finished()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;

    QNetworkReply* pReply = qobject_cast<QNetworkReply*>(sender());
    printDebugProxyData(pReply);

    Proxy* proxy = findProxy(pReply);
    if(proxy != nullptr){
        pReply->readAll();
        QVariant httpStatus = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(httpStatus.isValid()){
            qDebug() << "http status: " << httpStatus;
        }

        proxy->setTestReply(nullptr);
        QNetworkReply::NetworkError error = pReply->error();
        qDebug() << error;

        pReply->deleteLater();
    }

}

void
ProxyChecker::onRequest_metaDataChanged()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_sslErrors(const QList<QSslError> & errors)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;

    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));

    foreach(const QSslError& error, errors)
        qDebug() << "\t\tSSL error: " << error.errorString();
}

void
ProxyChecker::onRequest_preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(authenticator)

    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_redirected(const QUrl &url)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug()    << "\t\t" << url.toString();
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug()    << "\t\t" << bytesSent << " out of " << bytesTotal;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_encrypted()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_destroyed(QObject* obj)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(qobject_cast<QNetworkReply*>(obj));
}

void
ProxyChecker::onRequest_aboutToClose()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_bytesWritten(qint64 bytes)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug()    << "\t\t" << bytes;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_channelBytesWritten(int channel, qint64 bytes)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug()    << "\t\t" << "channel: " << channel << "; bytes: " << bytes;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_channelReadyRead(int channel)
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    qDebug()    << "\t\t" << "channel: " << channel;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_readChannelFinished()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;

    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onRequest_readyRead()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
    printDebugProxyData(qobject_cast<QNetworkReply*>(sender()));
}

void
ProxyChecker::onThread_started()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;

    QNetworkProxyFactory::setUseSystemConfiguration(false);

    if(m_pNetworkAccessMgr == nullptr)
    {
        m_pNetworkAccessMgr = new QNetworkAccessManager();
        QAbstractNetworkCache* cache = m_pNetworkAccessMgr->cache();
        if(cache != nullptr)
            cache->clear();
        m_pNetworkAccessMgr->moveToThread(currentThread());

        connect(m_pNetworkAccessMgr, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(onNetwork_authenticationRequired(QNetworkReply*,QAuthenticator*)));
        connect(m_pNetworkAccessMgr, SIGNAL(encrypted(QNetworkReply*)), SLOT(onNetwork_encrypted(QNetworkReply*)));
        connect(m_pNetworkAccessMgr, SIGNAL(finished(QNetworkReply*)), SLOT(onNetwork_finished(QNetworkReply*)));
        connect(m_pNetworkAccessMgr, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), SLOT(onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
        connect(m_pNetworkAccessMgr, SIGNAL(networkSessionConnected()), SLOT(onNetwork_networkSessionConnected()));
        connect(m_pNetworkAccessMgr, SIGNAL(preSharedKeyAuthenticationRequired(QNetworkReply*,QSslPreSharedKeyAuthenticator*)), SLOT(onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply*,QSslPreSharedKeyAuthenticator*)));
        connect(m_pNetworkAccessMgr, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)), SLOT(onNetwork_proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)));
        connect(m_pNetworkAccessMgr, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), SLOT(onNetwork_sslErrors(QNetworkReply*,QList<QSslError>)));
    }

    switch(m_SimultaneousCount)
    {
    case -1:
        testAllProxiesAtOnce();
        break;
    case 1:
        testProxiesOneByOne();
        break;
    default:
        testProxiesInChunksOf(m_SimultaneousCount);
        break;
    }
}

void
ProxyChecker::onThread_finished()
{
    qDebug()    << __FILE__ << ": " << __LINE__ << " -> " << __FUNCTION__;
}
