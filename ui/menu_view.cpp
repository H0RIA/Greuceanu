#include "sidemenu/menu_accounts.h"
#include "sidemenu/menu_agents.h"
#include "sidemenu/menu_proxies.h"
#include "sidemenu/menu_sessions.h"
#include "sidemenu/menu_settings.h"
#include "../mainwindow.h"
#include "menu_view.h"

using namespace UI;

MenuView::MenuView(QWidget* parent)
    :   QLabel(parent)
        ,m_lblIcon(this)
        ,m_lblTitle(this)
        ,m_btnSave(this)
        ,m_btnOpen(this)
        ,m_btnAdd(this)
        ,m_menus()
        ,m_pMainWindow(qobject_cast<MainWindow*>(parent))
{
    initializeData();
}

void
MenuView::on_save()
{
}

void
MenuView::on_open()
{
}

void
MenuView::on_add()
{
}

void
MenuView::initializeData()
{
    setObjectName("menu_view");

    QHBoxLayout* topLayoutBackground = new QHBoxLayout();
    QLabel* topBackground = new QLabel();
    QHBoxLayout* topLayout = new QHBoxLayout();

    topBackground->setObjectName("top_background");

    m_lblIcon.setObjectName("menu_view_icon");
    m_lblTitle.setObjectName("menu_view_title");
    m_btnSave.setObjectName("menu_view_btn_save");
    m_btnOpen.setObjectName("menu_view_btn_open");
    m_btnAdd.setObjectName("menu_view_btn_add");

    m_btnSave.setFlat(true);
    m_btnOpen.setFlat(true);
    m_btnAdd.setFlat(true);

    topBackground->setLayout(topLayout);
    topLayoutBackground->addWidget(topBackground);

    topLayout->addSpacing(2);
    topLayout->addWidget(&m_lblIcon);
    topLayout->addWidget(&m_lblTitle);
    topLayout->addStretch();
    topLayout->addWidget(&m_btnSave);
    topLayout->addSpacing(2);
    topLayout->addWidget(&m_btnOpen);
    topLayout->addSpacing(2);
    topLayout->addWidget(&m_btnAdd);
    topLayout->addSpacing(2);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    m_menus[SideMenuItem::Agents] = new SideMenu::MenuAgents(this);
    m_menus[SideMenuItem::Proxies] = new SideMenu::MenuProxies(this);
    m_menus[SideMenuItem::Sessions] = new SideMenu::MenuSessions(this);
    m_menus[SideMenuItem::Settings] = new SideMenu::MenuSettings(this);
    m_menus[SideMenuItem::Users] = new SideMenu::MenuAccounts(this);

    mainLayout->addLayout(topLayoutBackground);
    mainLayout->addSpacing(10);

    mainLayout->addWidget(m_menus[SideMenuItem::Agents]);
    mainLayout->addWidget(m_menus[SideMenuItem::Proxies]);
    mainLayout->addWidget(m_menus[SideMenuItem::Sessions]);
    mainLayout->addWidget(m_menus[SideMenuItem::Settings]);
    mainLayout->addWidget(m_menus[SideMenuItem::Users]);

    setLayout(mainLayout);

    connect(&m_btnAdd, SIGNAL(clicked()), SLOT(on_add()));
    connect(&m_btnOpen, SIGNAL(clicked()), SLOT(on_open()));
    connect(&m_btnSave, SIGNAL(clicked()), SLOT(on_save()));
}

void
MenuView::enable_menu(SideMenuItem menu)
{
    SideMenuItem currentActiveItem = SideMenuItem::None;
    MainWindow* mainWnd = qobject_cast<MainWindow*>(m_pMainWindow);
    if(mainWnd != nullptr){
        currentActiveItem = mainWnd->getNavBar()->getActiveMenu();
    }else{
        qDebug() << "Error in " << __FILE__ << " at line: " << __LINE__;
    }

    foreach(QWidget* menu, m_menus)
        menu->hide();

    if(m_menus.contains(menu))
        m_menus[menu]->show();

    switch(menu)
    {
    case SideMenuItem::Agents:
        m_lblIcon.setObjectName("menu_view_icon_agents");
        m_lblTitle.setText(tr("Agents"));
        break;
    case SideMenuItem::Proxies:
        m_lblIcon.setObjectName("menu_view_icon_proxies");
        m_lblTitle.setText(tr("Proxies"));
        break;
    case SideMenuItem::Sessions:
        m_lblIcon.setObjectName("menu_view_icon_sessions");
        m_lblTitle.setText(tr("Sessions"));
        break;
    case SideMenuItem::Settings:
        m_lblIcon.setObjectName("menu_view_icon_settings");
        m_lblTitle.setText(tr("Settings"));
        break;
    case SideMenuItem::Users:
        m_lblIcon.setObjectName("menu_view_icon_users");
        m_lblTitle.setText(tr("Accounts"));
        break;
    default:
        break;
    }

    style()->polish(&m_lblIcon);
    m_lblIcon.repaint();
}
