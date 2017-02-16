#-------------------------------------------------
#
# Project created by QtCreator 2015-09-17T14:56:40
#
#-------------------------------------------------

QT       += core gui network svg webenginewidgets

macx:QMAKE_CXXFLAGS += -std=c++11
macx:CONFIG += c++11


macx:LIBS -= -lcrypto -lssl
#macx:LIBS += /usr/local/ssl/macos-x86_64/lib/libssl.a
#macx:LIBS += /usr/local/ssl/macos-x86_64/lib/libcrypto.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtBrowser
TEMPLATE = app


SOURCES += main.cpp\
    data/page.cpp \
    mainwindow.cpp \
    data/proxy.cpp \
    ui/tab_bar.cpp \
    ui/nav_bar.cpp \
    ui/page_view.cpp \
    ui/url_edit.cpp \
    ui/settings/settings_accounts.cpp \
    ui/settings/settings_agents.cpp \
    ui/settings/settings_general.cpp \
    ui/settings/settings_page.cpp \
    ui/settings/settings_proxies.cpp \
    ui/settings/settings_sessions.cpp \
    ui/settings/dialog_account.cpp \
    ui/settings/dialog_agent.cpp \
    ui/settings/dialog_proxy.cpp \
    ui/settings/dialog_session.cpp \
    ui/settings/dialog_site.cpp \
    ui/settings/dialog.cpp \
    ui/web_view.cpp \
    ui/theme.cpp \
    ui/menu_view.cpp \
    ui/sidemenu/menu_agents.cpp \
    ui/sidemenu/menu_sessions.cpp \
    ui/sidemenu/menu_accounts.cpp \
    ui/sidemenu/menu_proxies.cpp \
    ui/sidemenu/menu_settings.cpp \
    data/agent.cpp \
    data/user.cpp \
    data/proxy_checker.cpp

HEADERS  += \
    base.h \
    data/proxy.h \
    data/user.h \
    data/agent.h \
    data/session.h \
    data/page.h \
    mainwindow.h \
    ui/tab_bar.h \
    ui/url_edit.h \
    ui/nav_bar.h \
    ui/page_view.h \
    ui/web_view.h \
    ui/settings/settings_general.h \
    ui/settings/settings_sessions.h \
    ui/settings/settings_agents.h \
    ui/settings/settings_proxies.h \
    ui/settings/settings_accounts.h \
    ui/settings/dialog_session.h \
    ui/settings/dialog_agent.h \
    ui/settings/dialog_proxy.h \
    ui/settings/dialog_account.h \
    ui/settings/dialog_site.h \
    ui/settings/settings_page.h \
    ui/settings/dialog.h \
    ui/theme.h \
    ui/menu_view.h \
    ui/sidemenu/menu_agents.h \
    ui/sidemenu/menu_sessions.h \
    ui/sidemenu/menu_accounts.h \
    ui/sidemenu/menu_proxies.h \
    ui/sidemenu/menu_settings.h \
    ui/sidemenu/model_agents.h \
    ui/sidemenu/model_proxies.h \
    data/proxy_checker.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    mainwindow.css \
    tabbar.css \
    navbar.css \
    url_edit.css \
    menu_view.css \
    menu_agents.css \
    menu_proxies.css \
    menu_settings.css \
    menu_sessions.css \
    menu_accounts.css
