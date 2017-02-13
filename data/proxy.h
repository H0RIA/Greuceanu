#ifndef PROXY
#define PROXY

#include "base.h"

namespace Data
{
    enum class ProxyStatus
    {
        Active,     // Last test ran succeeded
        Inactive,   // Last test ran failed
        Pending,    // Running the tests on the proxy
        Unknown     // No tests were ran
    };

    class Proxy : public QObject
    {
        Q_OBJECT

        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, Address)
        DECLARE_PROPERTY(QString, UserName)
        DECLARE_PROPERTY(QString, UserPass)
        DECLARE_PROPERTY(int, Port)
        DECLARE_PROPERTY(QDateTime, LastCheck)
        DECLARE_PROPERTY(ProxyStatus, LastStatus)

        public:
            Proxy(QObject* parent = nullptr);
            Proxy(const Proxy& proxy);
            virtual ~Proxy();

            Proxy& operator=(const Proxy& proxy);
            bool operator==(const Proxy& proxy)const;
            bool operator!=(const Proxy& proxy)const;
    };
}

#endif // PROXY

