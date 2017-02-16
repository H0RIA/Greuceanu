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

#ifndef NAV_BAR
#define NAV_BAR

#include "base.h"

namespace UI
{
    class UrlEdit;

    enum class SideMenuItem{
        None = 0,
        Sessions,
        Agents,
        Proxies,
        Users,
        Settings
    };

    class NavBar : public QLabel
    {
        Q_OBJECT

        public:
            NavBar(QWidget* parent = nullptr);

            SideMenuItem getActiveMenu()const;

        protected:
            void enableMenu(SideMenuItem menu = SideMenuItem::None);

            void initializeData();

        protected slots:
            void onSessionsClicked();
            void onAgentsClicked();
            void onProxiesClicked();
            void onUsersClicked();
            void onSettingsClicked();

        signals:
            void menu_sessions(bool enabled = true);
            void menu_agents(bool enabled = true);
            void menu_proxies(bool enabled = true);
            void menu_users(bool enabled = true);
            void menu_settings(bool enabled = true);
            void disable_sidemenu();

        protected:
            QPushButton m_btnBack;
            QPushButton m_btnForward;
            QPushButton m_btnReload;

            UrlEdit* m_pEdit;

            QPushButton m_btnSessions;
            QPushButton m_btnAgents;
            QPushButton m_btnProxies;
            QPushButton m_btnUsers;
            QPushButton m_btnSettings;

            SideMenuItem m_ActiveMenu;
    };
}

#endif // NAV_BAR

