#ifndef MENU_PROXIES
#define MENU_PROXIES

#include "base.h"

namespace UI
{
    namespace SideMenu
    {
        class MenuProxies : public QLabel
        {
            Q_OBJECT

            public:
                MenuProxies(QWidget* parent = nullptr);

            protected:
                void initializeData();
        };
    }
}

#endif // MENU_PROXIES

