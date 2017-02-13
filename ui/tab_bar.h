#ifndef TAB_BAR
#define TAB_BAR

#include "base.h"

namespace UI
{
    class TabBar : public QLabel
    {
        Q_OBJECT

        public:
            TabBar(QWidget* parent = nullptr);

        protected:
            void initializeData();

        protected slots:
            void onAddTab();

        signals:
            void newTab(const QUuid& tabId);

        protected:
            QTabBar m_Tabs;
            QPushButton m_AddButton;
    };
}

#endif // TAB_BAR

