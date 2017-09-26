#include "mainwindow.h"
#include "data/session.h"
#include "data/agent.h"
#include "data/proxy.h"
#include "data/user.h"
#include "data/proxy_checker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Core::initializeJSonNames();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Data::User user1;
    user1.setFirstName("Horia");
    user1.setLastName("Popa");
    user1.setPassword("1234qwer");
    user1.setUName("H0RIA");

    Data::Agent agent1;
    agent1.setAlias("Greuceanu");
    agent1.setBrowserAgent("Greuceanu browserul barosanilor");

    Data::Proxy proxy1;
    proxy1.setAddress("200.229.193.206");
    proxy1.setPort(3128);

    Data::Session session1;
    session1.setName("Session001");

    Data::Page page1;
    page1.setName("Google");
    page1.setUrl("https://www.google.com");
    page1.setAgentId(agent1.Id());
    page1.setProxyEnabled(true);
    page1.setProxyId(proxy1.Id());
    page1.setSessionId(session1.Id());

    Data::Page page2;
    page2.setName("Google Romania");
    page2.setUrl("https://www.google.ro");
    page2.setAgentId(agent1.Id());
    page2.setProxyEnabled(true);
    page2.setProxyId(proxy1.Id());
    page2.setSessionId(session1.Id());

    session1.addPage(page1);
    session1.addPage(page2);

//    QJsonDocument document;

//    QJsonObject obj;
//    session1.write(obj);
//    document.setObject(obj);
//    QString data = document.toJson();
//    qDebug() << data;

    Data::ProxyChecker* checker = new Data::ProxyChecker(&w);
    checker->addProxy(proxy1);

    {
        Data::Proxy proxy;
        proxy.setAddress("94.242.55.177");
        proxy.setPort(8080);
        checker->addProxy(proxy);
    }

    {
        Data::Proxy proxy;
        proxy.setAddress("35.185.22.234");
        proxy.setPort(80);
        checker->addProxy(proxy);
    }

    checker->start();

    return a.exec();
}
