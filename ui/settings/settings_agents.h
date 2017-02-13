#ifndef SETTINGS_AGENTS
#define SETTINGS_AGENTS

#include "base.h"
#include "settings_page.h"

namespace UI
{
    namespace Settings
    {
        class Agents : public SettingsPage
        {
            Q_OBJECT

            public:
                Agents(QWidget* parent = nullptr);
        };
    }
}

#endif // SETTINGS_AGENTS

