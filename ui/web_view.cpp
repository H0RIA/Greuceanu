#include "web_view.h"

using namespace UI;

WebView::WebView(QWidget* parent)
#if (CURRENT_WEBVERSION == WEBVERSION_CHROMIUM)
    :   QWebEngineView(parent)
#else
    :   QWebView(parent)
#endif
{
}

void
WebView::load(const QUrl &url)
{
#if (CURRENT_WEBVERSION == WEBVERSION_CHROMIUM)
    QWebEngineView::load(url);
#else
    QWebView::load(url);
#endif
}

void
WebView::reload()
{
#if (CURRENT_WEBVERSION == WEBVERSION_CHROMIUM)
    QWebEngineView::reload();
#else
    QWebView::reload();
#endif
}
