#ifndef DIALOG_AGENT
#define DIALOG_AGENT

#include "base.h"
#include "dialog.h"

namespace UI
{
    namespace Settings
    {
        class AgentDialog : public Dialog
        {
            Q_OBJECT

            public:
                AgentDialog(QWidget* parent = nullptr);
        };
    }
}

#endif // DIALOG_AGENT

