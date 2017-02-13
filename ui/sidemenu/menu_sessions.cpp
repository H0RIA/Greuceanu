#include "menu_sessions.h"

using namespace UI::SideMenu;

MenuSessions::MenuSessions(QWidget* parent)
    :   QLabel(parent)
{
    initializeData();
}

void
MenuSessions::initializeData()
{
    setObjectName("menu_sessions");
}

