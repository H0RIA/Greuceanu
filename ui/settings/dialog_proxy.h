#ifndef DIALOG_PROXY
#define DIALOG_PROXY

#include "base.h"
#include "dialog.h"

namespace UI
{
    namespace Settings
    {
        class ProxyDialog : public Dialog
        {
            Q_OBJECT

            public:
                ProxyDialog(QWidget* parent = nullptr);
        };
    }
}

#endif // DIALOG_PROXY

