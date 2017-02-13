#ifndef DIALOG
#define DIALOG

#include "base.h"

namespace UI
{
    namespace Settings
    {
        class Dialog : public QDialog
        {
            Q_OBJECT

            public:
                Dialog(QWidget * parent = nullptr);
        };
    }
}

#endif // DIALOG

