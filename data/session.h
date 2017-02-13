#ifndef SESSION
#define SESSION

#include "base.h"

namespace Data
{
    class Page;

    class Session
    {
        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, Name)
        DECLARE_PROPERTY(QList<Data::Page*>, Pages)

        public:
            Session();
            Session(const Session& session);
            virtual ~Session();

            Session& operator=(const Session& session);
            bool operator==(const Session& session)const;
            bool operator!=(const Session& session)const;
    };
}

#endif // SESSION

