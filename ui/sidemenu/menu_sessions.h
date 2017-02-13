#ifndef MENU_SESSIONS
#define MENU_SESSIONS

#include "base.h"

namespace UI
{
    namespace SideMenu
    {
        class MenuSessions : public QLabel
        {
            Q_OBJECT

            public:
                MenuSessions(QWidget* parent = nullptr);

            protected:
                void initializeData();
        };
    }
}

#endif // MENU_SESSIONS

