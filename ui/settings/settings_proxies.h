#ifndef SETTINGS_PROXIES
#define SETTINGS_PROXIES

#include "base.h"
#include "settings_page.h"

namespace UI
{
    namespace Settings
    {
        class Proxies : public SettingsPage
        {
            Q_OBJECT

            public:
                Proxies(QWidget* parent = nullptr);
        };
    }
}

#endif // SETTINGS_PROXIES

