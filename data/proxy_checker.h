/*!
    \legalese

    Copyright 2017 Horia Popa

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following conditions:


    The above copyright notice and this permission notice shall be included in all copies
    or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
    THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    \endlegalese
*/

#ifndef PROXY_CHECKER_H
#define PROXY_CHECKER_H

#define DEFAULT_SLEEP_BETWEEN_RUNS      1000     // milliseconds

#include "proxy.h"

namespace Data
{
    class ProxyChecker : public QThread
    {
        Q_OBJECT

        typedef struct __ProxyTestInfo{
            public:
                __ProxyTestInfo()
                    :   _Proxy()
                        ,_pReply(nullptr)
                        ,_RunId(0)
                {}

                __ProxyTestInfo(const Data::Proxy& proxy)
                    :   _Proxy(proxy)
                        ,_pReply(nullptr)
                        ,_RunId(0)
                {}

                Data::Proxy _Proxy;
                QNetworkReply* _pReply;
                quint64 _RunId;

                inline bool operator ==(const __ProxyTestInfo& pti)const{return _Proxy.Id() == pti._Proxy.Id();}
                inline bool operator !=(const __ProxyTestInfo& pti)const{return !(this->operator ==(pti));}
        }ProxyTestInfo;

        private:
            DECLARE_PROPERTY_GREF(QList<ProxyTestInfo>, ProxyList)
            DECLARE_PROPERTY(bool, InfiniteLoop)
            DECLARE_PROPERTY(int, SimultaneousCount)
            DECLARE_PROPERTY_PTR(QNetworkAccessManager, NetworkAccessMgr)
            DECLARE_PROPERTY(quint64, CurrentRun)

        public:
            ProxyChecker(QObject *parent = nullptr);
            virtual ~ProxyChecker();

            bool addProxy(const Proxy& proxy);
            bool remProxy(const QUuid& proxyId);
            void clearProxies();

        protected:
            void testAllProxiesAtOnce();
            void testNextProxy();
            void testProxiesInChunksOf(int chunkSize);

            ProxyChecker::ProxyTestInfo* findProxy(QNetworkReply* reply);
            ProxyChecker::ProxyTestInfo* findProxy(const QUuid& id);
            ProxyChecker::ProxyTestInfo* findNextProxy();
            int activeTests()const;

        private:
            void printDebugProxyData(QNetworkReply* pReply);
            void newRun();

        protected slots:
            void onNetwork_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
            void onNetwork_encrypted(QNetworkReply *reply);
            void onNetwork_finished(QNetworkReply *reply);
            void onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
            void onNetwork_networkSessionConnected();
            void onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
            void onNetwork_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
            void onNetwork_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

            void onRequest_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
            void onRequest_error(QNetworkReply::NetworkError code);
            void onRequest_finished();
            void onRequest_metaDataChanged();
            void onRequest_sslErrors(const QList<QSslError> & errors);
            void onRequest_preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);
            void onRequest_redirected(const QUrl &url);
            void onRequest_uploadProgress(qint64 bytesSent, qint64 bytesTotal);
            void onRequest_encrypted();
            void onRequest_destroyed(QObject* obj);

            void onRequest_aboutToClose();
            void onRequest_bytesWritten(qint64 bytes);
            void onRequest_channelBytesWritten(int channel, qint64 bytes);
            void onRequest_channelReadyRead(int channel);
            void onRequest_readChannelFinished();
            void onRequest_readyRead();

            void onProxy_statusChanged(ProxyStatus newStatus);

        public slots:
            void onThread_started();
            void onThread_finished();

        signals:
            // Emitted when a run through the list of proxies has ended
            void finished(int runNumber);
            void proxyStatusChanged(Proxy* proxy, ProxyStatus newStatus);
    };
}

#endif // PROXY_CHECKER_H
