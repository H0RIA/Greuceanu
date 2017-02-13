#include "menu_agents.h"

using namespace UI::SideMenu;

MenuAgents::MenuAgents(QWidget* parent)
    :   QLabel(parent)
        ,m_lblLogo(this)
        ,m_lblTitle(this)
        ,m_btnAdd(this)
{
    initializeData();
}

void
MenuAgents::initializeData()
{
    setObjectName("menu_agents");

}
