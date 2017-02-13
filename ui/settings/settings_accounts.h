#ifndef SETTINGS_ACCOUNTS
#define SETTINGS_ACCOUNTS

#include "base.h"
#include "settings_page.h"

namespace UI
{
    namespace Settings
    {
        class Accounts : public SettingsPage
        {
            Q_OBJECT

            public:
                Accounts(QWidget* parent = nullptr);
        };
    }
}

#endif // SETTINGS_ACCOUNTS

