#ifndef MENU_SETTINGS
#define MENU_SETTINGS

#include "base.h"

namespace UI
{
    namespace SideMenu
    {
        class MenuSettings : public QLabel
        {
            Q_OBJECT

            public:
                MenuSettings(QWidget* parent = nullptr);

            protected:
                void initializeData();
        };
    }
}

#endif // MENU_SETTINGS

