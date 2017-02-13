#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "base.h"

namespace UI
{
    class PageView;
    class TabBar;
    class NavBar;
    class MenuView;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        UI::NavBar* getNavBar();

    protected:
        void initializeData();

    protected slots:
        void on_newTab(const QUuid& id);

        void on_menu_sessions(bool enabled = true);
        void on_menu_agents(bool enabled = true);
        void on_menu_proxies(bool enabled = true);
        void on_menu_users(bool enabled = true);
        void on_menu_settings(bool enabled = true);
        void on_disable_sidemenu();

    protected:
        UI::TabBar* m_pTabBar;
        UI::NavBar* m_pNavBar;
        UI::PageView* m_pPageView;
        UI::MenuView* m_pMenuView;
};

#endif // MAINWINDOW_H
