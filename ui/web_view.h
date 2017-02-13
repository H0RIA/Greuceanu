#ifndef WEB_VIEW
#define WEB_VIEW

#include "base.h"
#include "data/page.h"
#include "data/session.h"

namespace UI
{
#if (CURRENT_WEBVERSION == WEBVERSION_CHROMIUM)
    class WebView : public QWebEngineView
#else
    class WebView : public QWebView
#endif
    {
        Q_OBJECT

        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY_PTR(Data::Page, PageData)

        public:
            WebView(QWidget* parent = nullptr);

        public slots:
            void load(const QUrl &url);
            void reload();
    };
}

#endif // WEB_VIEW

