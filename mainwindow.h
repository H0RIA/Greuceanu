/*!
    \legalese

    Copyright 2017 Horia Popa

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following conditions:


    The above copyright notice and this permission notice shall be included in all copies
    or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
    THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    \endlegalese
*/

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
