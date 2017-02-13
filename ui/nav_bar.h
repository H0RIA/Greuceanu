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

