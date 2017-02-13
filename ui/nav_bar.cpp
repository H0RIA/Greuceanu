#include "url_edit.h"
#include "nav_bar.h"

using namespace UI;

NavBar::NavBar(QWidget* parent)
    :   QLabel(parent)
        ,m_btnBack(this)
        ,m_btnForward(this)
        ,m_btnReload(this)
        ,m_pEdit(nullptr)
        ,m_btnSessions(this)
        ,m_btnAgents(this)
        ,m_btnProxies(this)
        ,m_btnUsers(this)
        ,m_btnSettings(this)
        ,m_ActiveMenu(SideMenuItem::None)
{
    initializeData();
}

SideMenuItem
NavBar::getActiveMenu()const
{
    return m_ActiveMenu;
}

void
NavBar::enableMenu(SideMenuItem menu)
{
    m_ActiveMenu = menu;

    switch(m_ActiveMenu)
    {
    case SideMenuItem::Agents:
        m_btnSessions.setChecked(false);
        m_btnProxies.setChecked(false);
        m_btnUsers.setChecked(false);
        m_btnSettings.setChecked(false);
        break;
    case SideMenuItem::Proxies:
        m_btnSessions.setChecked(false);
        m_btnAgents.setChecked(false);
        m_btnUsers.setChecked(false);
        m_btnSettings.setChecked(false);
        break;
    case SideMenuItem::Sessions:
        m_btnAgents.setChecked(false);
        m_btnProxies.setChecked(false);
        m_btnUsers.setChecked(false);
        m_btnSettings.setChecked(false);
        break;
    case SideMenuItem::Settings:
        m_btnSessions.setChecked(false);
        m_btnAgents.setChecked(false);
        m_btnProxies.setChecked(false);
        m_btnUsers.setChecked(false);
        break;
    case SideMenuItem::Users:
        m_btnSessions.setChecked(false);
        m_btnAgents.setChecked(false);
        m_btnProxies.setChecked(false);
        m_btnSettings.setChecked(false);
        break;
    case SideMenuItem::None:
        m_btnSessions.setChecked(false);
        m_btnAgents.setChecked(false);
        m_btnProxies.setChecked(false);
        m_btnUsers.setChecked(false);
        m_btnSettings.setChecked(false);
        break;
    }
}

void
NavBar::initializeData()
{
    QHBoxLayout* layoutNav = new QHBoxLayout();
    QHBoxLayout* layoutSettings = new QHBoxLayout();
    QHBoxLayout* mainLayout = new QHBoxLayout();

    connect(&m_btnAgents, SIGNAL(clicked()), SLOT(onAgentsClicked()));
    connect(&m_btnProxies, SIGNAL(clicked()), SLOT(onProxiesClicked()));
    connect(&m_btnSessions, SIGNAL(clicked()), SLOT(onSessionsClicked()));
    connect(&m_btnSettings, SIGNAL(clicked()), SLOT(onSettingsClicked()));
    connect(&m_btnUsers, SIGNAL(clicked()), SLOT(onUsersClicked()));

    m_btnBack.setFlat(true);
    m_btnForward.setFlat(true);
    m_btnReload.setFlat(true);

    m_btnAgents.setCheckable(true);
    m_btnSessions.setCheckable(true);
    m_btnProxies.setCheckable(true);
    m_btnUsers.setCheckable(true);
    m_btnSettings.setCheckable(true);

    m_btnAgents.setFlat(true);
    m_btnSessions.setFlat(true);
    m_btnProxies.setFlat(true);
    m_btnUsers.setFlat(true);
    m_btnSettings.setFlat(true);

    m_btnBack.setObjectName("navbar_btn_back");
    m_btnForward.setObjectName("navbar_btn_forward");
    m_btnReload.setObjectName("navbar_btn_reload");

    m_btnAgents.setObjectName("navbar_btn_aggents");
    m_btnSessions.setObjectName("navbar_btn_sessions");
    m_btnProxies.setObjectName("navbar_btn_proxies");
    m_btnUsers.setObjectName("navbar_btn_users");
    m_btnSettings.setObjectName("navbar_btn_settings");

    m_pEdit = new UrlEdit(this);

    layoutNav->setContentsMargins(0, 0, 0, 0);
    layoutNav->setSpacing(0);

    layoutSettings->setContentsMargins(0, 0, 0, 0);
    layoutSettings->setSpacing(0);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    layoutNav->addWidget(&m_btnBack, 0, Qt::AlignVCenter);
    layoutNav->addWidget(&m_btnForward, 0, Qt::AlignVCenter);
    layoutNav->addWidget(&m_btnReload, 0, Qt::AlignVCenter);

    layoutSettings->addWidget(&m_btnSessions, 0, Qt::AlignVCenter);
    layoutSettings->addWidget(&m_btnAgents, 0, Qt::AlignVCenter);
    layoutSettings->addWidget(&m_btnProxies, 0, Qt::AlignVCenter);
    layoutSettings->addWidget(&m_btnUsers, 0, Qt::AlignVCenter);
    layoutSettings->addWidget(&m_btnSettings, 0, Qt::AlignVCenter);

    mainLayout->addSpacing(10);
    mainLayout->addLayout(layoutNav);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_pEdit, 0, Qt::AlignVCenter);
    mainLayout->addStretch();
    mainLayout->addLayout(layoutSettings);
    mainLayout->addSpacing(10);

    setLayout(mainLayout);
}

void
NavBar::onSessionsClicked()
{
    if(m_ActiveMenu == SideMenuItem::Sessions){
        enableMenu(SideMenuItem::None);
        emit disable_sidemenu();
    }else{
        enableMenu(SideMenuItem::Sessions);
        emit menu_sessions();
    }
}

void
NavBar::onAgentsClicked()
{
    if(m_ActiveMenu == SideMenuItem::Agents){
        enableMenu(SideMenuItem::None);
        emit disable_sidemenu();
    }else{
        enableMenu(SideMenuItem::Agents);
        emit menu_agents();
    }
}

void
NavBar::onProxiesClicked()
{
    if(m_ActiveMenu == SideMenuItem::Proxies){
        enableMenu(SideMenuItem::None);
        emit disable_sidemenu();
    }else{
        enableMenu(SideMenuItem::Proxies);
        emit menu_proxies();
    }
}

void
NavBar::onUsersClicked()
{
    if(m_ActiveMenu == SideMenuItem::Users){
        enableMenu(SideMenuItem::None);
        emit disable_sidemenu();
    }else{
        enableMenu(SideMenuItem::Users);
        emit menu_users();
    }
}

void
NavBar::onSettingsClicked()
{
    if(m_ActiveMenu == SideMenuItem::Settings){
        enableMenu(SideMenuItem::None);
        emit disable_sidemenu();
    }else{
        enableMenu(SideMenuItem::Settings);
        emit menu_settings();
    }
}
