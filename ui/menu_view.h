#ifndef MENU_VIEW
#define MENU_VIEW

#include "nav_bar.h"

class MainWindow;

namespace UI
{
    class MenuView : public QLabel
    {
        Q_OBJECT

        public:
            MenuView(QWidget* parent = nullptr);

            void enable_menu(SideMenuItem menu = SideMenuItem::Sessions);

        protected slots:
            void on_save();
            void on_open();
            void on_add();

        protected:
            void initializeData();

        protected:
            QLabel m_lblIcon;
            QLabel m_lblTitle;

            QPushButton m_btnSave;
            QPushButton m_btnOpen;
            QPushButton m_btnAdd;

            QMap<SideMenuItem, QWidget*> m_menus;
            MainWindow* m_pMainWindow;
    };
}

#endif // MENU_VIEW

