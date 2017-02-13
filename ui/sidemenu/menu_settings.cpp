#include "menu_settings.h"

using namespace UI::SideMenu;

MenuSettings::MenuSettings(QWidget* parent)
    :   QLabel(parent)
{
    initializeData();
}

void
MenuSettings::initializeData()
{
    setObjectName("menu_settings");
}
