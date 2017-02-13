#ifndef USER
#define USER

#include "base.h"

namespace Data
{
    class User
    {
        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, UName)
        DECLARE_PROPERTY(QString, Password)
        DECLARE_PROPERTY(QString, FirstName)
        DECLARE_PROPERTY(QString, LastName)

        public:
            User();
            User(const User& user);
            virtual ~User();

            User& operator=(const User& user);
            bool operator==(const User& user)const;
            bool operator!=(const User& user)const;
    };
}

#endif // USER
