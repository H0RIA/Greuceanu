#ifndef MENU_AGENTS
#define MENU_AGENTS

#include "base.h"

namespace UI
{
    namespace SideMenu
    {
        class MenuAgents : public QLabel
        {
            Q_OBJECT

            public:
                MenuAgents(QWidget* parent = nullptr);

            protected:
                void initializeData();

            protected:
                QLabel m_lblLogo;
                QLabel m_lblTitle;
                QPushButton m_btnAdd;
                QTableView m_lstAgents;
        };
    }
}

#endif // MENU_AGENTS

