#include "menu_proxies.h"

using namespace UI::SideMenu;

MenuProxies::MenuProxies(QWidget* parent)
    :   QLabel(parent)
{
    initializeData();
}

void
MenuProxies::initializeData()
{
    setObjectName("menu_proxies");
}



