#ifndef SETTINGS_PAGE
#define SETTINGS_PAGE

#include "base.h"
#include "settings_page.h"

namespace UI
{
    namespace Settings
    {
        class SettingsPage : public QLabel
        {
            Q_OBJECT

            public:
                SettingsPage(QWidget* parent = nullptr);
        };
    }
}

#endif // SETTINGS_PAGE

