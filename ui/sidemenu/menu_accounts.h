#ifndef MENU_ACCOUNTS
#define MENU_ACCOUNTS

#include "base.h"

namespace UI
{
    namespace SideMenu
    {
        class MenuAccounts : public QLabel
        {
            Q_OBJECT

            public:
                MenuAccounts(QWidget* parent = nullptr);

            protected:
                void initializeData();
        };
    }
}


#endif // MENU_ACCOUNTS

