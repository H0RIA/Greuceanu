#include <QScreen>
#include "ui/nav_bar.h"
#include "ui/tab_bar.h"
#include "ui/web_view.h"
#include "ui/page_view.h"
#include "ui/menu_view.h"
#include "ui/theme.h"
#include "ui/nav_bar.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :   QMainWindow(parent)
        ,m_pTabBar(nullptr)
        ,m_pNavBar(nullptr)
        ,m_pPageView(nullptr)
        ,m_pMenuView(nullptr)
{
    initializeData();
}

MainWindow::~MainWindow()
{
}

UI::NavBar*
MainWindow::getNavBar()
{
    return m_pNavBar;
}

void
MainWindow::initializeData()
{
    UI::Theme defaultTheme(":/themes/mainwindow.css");
    defaultTheme.addCssFile(":/themes/navbar.css");
    defaultTheme.addCssFile(":/themes/tabbar.css");
    defaultTheme.addCssFile(":/themes/url_edit.css");
    defaultTheme.addCssFile(":/themes/menu_view.css");
    defaultTheme.addCssFile(":/themes/menu_agents.css");
    defaultTheme.addCssFile(":/themes/menu_proxies.css");
    defaultTheme.addCssFile(":/themes/menu_settings.css");
    defaultTheme.addCssFile(":/themes/menu_sessions.css");
    defaultTheme.addCssFile(":/themes/menu_accounts.css");

    qApp->setStyleSheet(defaultTheme.load());

    QList<QScreen*> screenList = QApplication::screens();
    if(!screenList.isEmpty()){
        QScreen* mainScreen = screenList.first();
        if(mainScreen != nullptr){
            setGeometry(mainScreen->availableGeometry());
        }
    }

    m_pTabBar = new UI::TabBar(this);
    m_pNavBar = new UI::NavBar(this);
    m_pPageView = new UI::PageView(this);
    m_pMenuView = new UI::MenuView(this);

    m_pMenuView->setVisible(false);

    QWidget* container = new QWidget();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* centralPageLayout = new QHBoxLayout();

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    centralPageLayout->setContentsMargins(0, 0, 0, 0);
    centralPageLayout->setSpacing(0);

    centralPageLayout->addWidget(m_pPageView);
    centralPageLayout->addWidget(m_pMenuView);

    mainLayout->addWidget(m_pTabBar);
    mainLayout->addWidget(m_pNavBar);
    mainLayout->addLayout(centralPageLayout);

    container->setLayout(mainLayout);

    setCentralWidget(container);

    // Connect signals
    connect(m_pTabBar, SIGNAL(newTab(QUuid)), SLOT(on_newTab(QUuid)));

    connect(m_pNavBar, SIGNAL(menu_agents(bool)), SLOT(on_menu_agents(bool)));
    connect(m_pNavBar, SIGNAL(menu_proxies(bool)), SLOT(on_menu_proxies(bool)));
    connect(m_pNavBar, SIGNAL(menu_sessions(bool)), SLOT(on_menu_sessions(bool)));
    connect(m_pNavBar, SIGNAL(menu_settings(bool)), SLOT(on_menu_settings(bool)));
    connect(m_pNavBar, SIGNAL(menu_users(bool)), SLOT(on_menu_users(bool)));
    connect(m_pNavBar, SIGNAL(disable_sidemenu()), SLOT(on_disable_sidemenu()));
}

void
MainWindow::on_newTab(const QUuid& id)
{
    if(id.isNull())
        return;

    m_pPageView->onAddTab(id);
}

void
MainWindow::on_menu_sessions(bool enabled)
{
    if(enabled){
        if(!m_pMenuView->isVisible())
            m_pMenuView->show();

        m_pMenuView->enable_menu(UI::SideMenuItem::Sessions);
    }else{
        on_disable_sidemenu();
    }
}

void
MainWindow::on_menu_agents(bool enabled)
{
    if(enabled){
        if(!m_pMenuView->isVisible())
            m_pMenuView->show();

        m_pMenuView->enable_menu(UI::SideMenuItem::Agents);
    }else{
        on_disable_sidemenu();
    }
}

void
MainWindow::on_menu_proxies(bool enabled)
{
    if(enabled){
        if(!m_pMenuView->isVisible())
            m_pMenuView->show();

        m_pMenuView->enable_menu(UI::SideMenuItem::Proxies);
    }else{
        on_disable_sidemenu();
    }
}

void
MainWindow::on_menu_users(bool enabled)
{
    if(enabled){
        if(!m_pMenuView->isVisible())
            m_pMenuView->show();

        m_pMenuView->enable_menu(UI::SideMenuItem::Users);
    }else{
        on_disable_sidemenu();
    }
}

void
MainWindow::on_menu_settings(bool enabled)
{
    if(enabled){
        if(!m_pMenuView->isVisible())
            m_pMenuView->show();

        m_pMenuView->enable_menu(UI::SideMenuItem::Settings);
    }else{
        on_disable_sidemenu();
    }
}

void
MainWindow::on_disable_sidemenu()
{
    m_pMenuView->hide();
}
