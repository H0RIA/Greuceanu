#include "url_edit.h"

using namespace UI;

UrlEdit::UrlEdit(QWidget* parent)
    :   QLineEdit(parent)
{
    initializeData();
}

void
UrlEdit::initializeData()
{
    setObjectName("url_edit");
    setAttribute(Qt::WA_MacShowFocusRect, 0);
}
