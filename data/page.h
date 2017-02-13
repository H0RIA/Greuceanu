#ifndef PAGE
#define PAGE

#include "base.h"

namespace Data
{
    class Page
    {
        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, Name)
        DECLARE_PROPERTY(QString, Url)
        DECLARE_PROPERTY(QUuid, ProxyId)
        DECLARE_PROPERTY(bool, ProxyEnabled)
        DECLARE_PROPERTY(QUuid, AgentId)
        DECLARE_PROPERTY(QUuid, SessionId)

        public:
            Page();
            Page(const Page& page);
            virtual ~Page();

            Page& operator=(const Page& page);
            bool operator==(const Page& page)const;
            bool operator!=(const Page& page)const;
    };
}

#endif // PAGE

