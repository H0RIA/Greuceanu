#ifndef DIALOG_SESSION
#define DIALOG_SESSION

#include "base.h"
#include "dialog.h"

namespace UI
{
    namespace Settings
    {
        class SessionDialog : public Dialog
        {
            Q_OBJECT

            public:
                SessionDialog(QWidget* parent = nullptr);
        };
    }
}

#endif // DIALOG_SESSION

