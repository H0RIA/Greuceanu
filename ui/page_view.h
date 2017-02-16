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

#ifndef PAGE_VIEW
#define PAGE_VIEW

#include "base.h"

namespace UI
{
    class PageView : public QLabel
    {
        Q_OBJECT

        public:
            PageView(QWidget* parent = nullptr);

        public slots:
            void onAddTab(const QUuid& id);

        protected slots:
            void on_iconChanged();
            void on_linkClicked(const QUrl & url);
            void on_loadFinished(bool ok);
            void on_loadProgress(int progress);
            void on_loadStarted();
            void on_selectionChanged();
            void on_statusBarMessage(const QString & text);
            void on_titleChanged(const QString & title);
            void on_urlChanged(const QUrl & url);

        protected:
            void initializeData();

        signals:
            void iconChanged(const QUuid& pageId);
            void linkClicked(const QUuid& pageId, const QUrl & url);
            void loadFinished(const QUuid& pageId, bool ok);
            void loadProgress(const QUuid& pageId, int progress);
            void loadStarted(const QUuid& pageId);
            void selectionChanged(const QUuid& pageId);
            void statusBarMessage(const QUuid& pageId, const QString & text);
            void titleChanged(const QUuid& pageId, const QString & title);
            void urlChanged(const QUuid& pageId, const QUrl & url);

        protected:
            QStackedWidget m_Pages;
            QStackedWidget m_Settings;
    };
}

#endif // PAGE_VIEW

