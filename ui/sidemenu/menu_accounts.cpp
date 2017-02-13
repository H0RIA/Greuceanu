#include "menu_accounts.h"

using namespace UI::SideMenu;

MenuAccounts::MenuAccounts(QWidget* parent)
    :   QLabel(parent)
{
    initializeData();
}

void
MenuAccounts::initializeData()
{
    setObjectName("menu_accounts");
}


