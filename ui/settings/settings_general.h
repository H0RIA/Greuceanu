#ifndef SETTINGS_GENERAL
#define SETTINGS_GENERAL

#include "base.h"
#include "settings_page.h"

namespace UI
{
    namespace Settings
    {
        class General : public SettingsPage
        {
            Q_OBJECT

            public:
                General(QWidget* parent = nullptr);
        };
    }
}

#endif // SETTINGS_GENERAL

