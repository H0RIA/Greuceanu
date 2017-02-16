#include "proxy_checker.h"

using namespace Data;

ProxyChecker::ProxyChecker(QObject *parent)
    :   QThread(parent)
        ,m_ProxyList()
        ,m_InfiniteLoop(false)
        ,m_SimultaneousCount(1)
        ,m_pNetworkAccessMgr(nullptr)
{
}

ProxyChecker::~ProxyChecker(){}

void
ProxyChecker::run()
{
    if(m_pNetworkAccessMgr == nullptr){
        m_pNetworkAccessMgr = new QNetworkAccessManager(this);

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

}

void
ProxyChecker::testProxiesOneByOne()
{
}

void
ProxyChecker::testProxiesInChunksOf(int chunkSize)
{
}

void
ProxyChecker::onNetwork_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
}

void
ProxyChecker::onNetwork_encrypted(QNetworkReply *reply)
{
}

void
ProxyChecker::onNetwork_finished(QNetworkReply *reply)
{
}

void
ProxyChecker::onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
}

void
ProxyChecker::onNetwork_networkSessionConnected()
{
}

void
ProxyChecker::onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
}

void
ProxyChecker::onNetwork_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
}

void
ProxyChecker::onNetwork_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
}
