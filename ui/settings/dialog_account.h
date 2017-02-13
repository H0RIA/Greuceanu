#ifndef DIALOG_ACCOUNT
#define DIALOG_ACCOUNT

#include "base.h"
#include "dialog.h"

namespace UI
{
    namespace Settings
    {
        class AccountDialog : public Dialog
        {
            Q_OBJECT

            public:
                AccountDialog(QWidget* parent = nullptr);
        };
    }
}

#endif // DIALOG_ACCOUNT

