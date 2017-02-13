#ifndef DIALOG_SITE
#define DIALOG_SITE

#include "base.h"
#include "dialog.h"

namespace UI
{
    namespace Settings
    {
        class SiteDialog : public Dialog
        {
            Q_OBJECT

            public:
                SiteDialog(QWidget* parent = nullptr);
        };
    }
}


#endif // DIALOG_SITE

