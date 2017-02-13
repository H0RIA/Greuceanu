#ifndef SETTINGS_SESSIONS
#define SETTINGS_SESSIONS

#include "base.h"
#include "settings_page.h"

namespace UI
{
    namespace Settings
    {
        class Sessions : public SettingsPage
        {
            Q_OBJECT

            public:
                Sessions(QWidget* parent = nullptr);
        };
    }
}

#endif // SETTINGS_SESSIONS

