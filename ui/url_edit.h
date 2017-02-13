#ifndef URL_EDIT
#define URL_EDIT

#include "base.h"

namespace UI
{
    class UrlEdit : public QLineEdit
    {
        Q_OBJECT

        public:
            UrlEdit(QWidget* parent = nullptr);

        protected:
            void initializeData();
    };
}

#endif // URL_EDIT

