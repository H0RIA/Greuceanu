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

#include "proxy.h"

namespace Data
{
    class ProxyChecker : public QThread
    {
        Q_OBJECT
        //Q_DISABLE_COPY(ProxyChecker)

        private:
            DECLARE_PROPERTY_GREF(QList<Data::Proxy>, ProxyList)
            DECLARE_PROPERTY(bool, InfiniteLoop)
            DECLARE_PROPERTY(bool, SimultaneousCount)
            DECLARE_PROPERTY_PTR(QNetworkAccessManager, NetworkAccessMgr)


        public:
            ProxyChecker(QObject *parent = nullptr);
            virtual ~ProxyChecker();

            virtual void run() override;

            bool addProxy(const Proxy& proxy);
            bool remProxy(const QUuid& proxyId);
            void clearProxies();

        protected:
            void testAllProxiesAtOnce();
            void testProxiesOneByOne();
            void testProxiesInChunksOf(int chunkSize);

        protected slots:
            void onNetwork_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
            void onNetwork_encrypted(QNetworkReply *reply);
            void onNetwork_finished(QNetworkReply *reply);
            void onNetwork_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
            void onNetwork_networkSessionConnected();
            void onNetwork_preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
            void onNetwork_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
            void onNetwork_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

        signals:
            // Emitted when a run through the list of proxies has ended
            void finished(int runNumber);
    };
}

#endif // PROXY_CHECKER_H
