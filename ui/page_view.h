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

