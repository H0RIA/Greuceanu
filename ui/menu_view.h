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

