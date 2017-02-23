#include "mainwindow.h"
#include "data/proxy_checker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Data::ProxyChecker* checker = new Data::ProxyChecker(&w);

    {
        Data::Proxy proxy;
        proxy.setAddress("200.229.193.206");
        proxy.setPort(3128);
        checker->addProxy(proxy);
    }

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
