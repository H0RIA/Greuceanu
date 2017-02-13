#include "ui/settings/settings_accounts.h"
#include "ui/settings/settings_agents.h"
#include "ui/settings/settings_general.h"
#include "ui/settings/settings_proxies.h"
#include "ui/settings/settings_sessions.h"
#include "ui/web_view.h"
#include "page_view.h"

using namespace UI;

PageView::PageView(QWidget* parent)
    :   QLabel(parent)
        ,m_Pages(this)
        ,m_Settings(this)
{
    initializeData();
}

void
PageView::onAddTab(const QUuid& id)
{
    if(id.isNull())
        return;

    UI::WebView* view = new UI::WebView(this);
    if(view == nullptr)
        return;

    connect(view, SIGNAL(iconChanged()), SLOT(on_iconChanged()));
    connect(view, SIGNAL(linkClicked(QUrl)), SLOT(on_linkClicked(QUrl)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(on_loadFinished(bool)));
    connect(view, SIGNAL(loadProgress(int)), SLOT(on_loadProgress(int)));
    connect(view, SIGNAL(loadStarted()), SLOT(on_loadStarted()));
    connect(view, SIGNAL(selectionChanged()), SLOT(on_selectionChanged()));
    connect(view, SIGNAL(statusBarMessage(QString)), SLOT(on_statusBarMessage(QString)));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(on_titleChanged(QString)));
    connect(view, SIGNAL(urlChanged(QUrl)), SLOT(on_urlChanged(QUrl)));

    view->setId(id);
    view->load(QString("http://www.google.com"));
    m_Pages.addWidget(view);
}

void
PageView::on_iconChanged()
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit iconChanged(idView);
}

void
PageView::on_linkClicked(const QUrl & url)
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit linkClicked(idView, url);
}

void
PageView::on_loadFinished(bool ok)
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit loadFinished(idView, ok);
}

void
PageView::on_loadProgress(int progress)
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit loadProgress(idView, progress);
}

void
PageView::on_loadStarted()
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit loadStarted(idView);
}

void
PageView::on_selectionChanged()
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit selectionChanged(idView);
}

void
PageView::on_statusBarMessage(const QString & text)
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit statusBarMessage(idView, text);
}

void
PageView::on_titleChanged(const QString & title)
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit titleChanged(idView, title);
}

void
PageView::on_urlChanged(const QUrl & url)
{
    WebView* view = qobject_cast<WebView*>(sender());
    if(view == nullptr)
        return;

    QUuid idView = view->Id();
    emit urlChanged(idView, url);
}

void
PageView::initializeData()
{
    setObjectName("page_view");
    m_Pages.setObjectName("pageview_pages");

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(2);

    UI::Settings::Accounts* accounts = new UI::Settings::Accounts(this);
    UI::Settings::Agents* agents = new UI::Settings::Agents(this);
    UI::Settings::General* general = new UI::Settings::General(this);
    UI::Settings::Proxies* proxies = new UI::Settings::Proxies(this);
    UI::Settings::Sessions* sessions = new UI::Settings::Sessions(this);

    m_Settings.addWidget(accounts);
    m_Settings.addWidget(agents);
    m_Settings.addWidget(general);
    m_Settings.addWidget(proxies);
    m_Settings.addWidget(sessions);

    m_Settings.hide();

    mainLayout->addWidget(&m_Pages);
    mainLayout->addWidget(&m_Settings);

    setLayout(mainLayout);
}
