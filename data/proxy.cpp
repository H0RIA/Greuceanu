#include "proxy.h"

using namespace Data;

Proxy::Proxy(QObject* parent)
    :   QObject(parent)
        ,m_Id(QUuid::createUuid())
        ,m_Address()
        ,m_UserName()
        ,m_UserPass()
        ,m_Port(0)
        ,m_LastCheck()
        ,m_LastStatus(ProxyStatus::Unknown)
        ,m_TestUrl(DEFAULT_TEST_URL)
        ,m_pTimeoutTimer(nullptr)
{
    initializeTimer();
}

Proxy::Proxy(const Proxy& proxy)
    :   QObject()
        ,m_Id(proxy.Id())
        ,m_Address(proxy.Address())
        ,m_UserName(proxy.UserName())
        ,m_UserPass(proxy.UserPass())
        ,m_Port(proxy.Port())
        ,m_LastCheck(proxy.LastCheck())
        ,m_LastStatus(proxy.LastStatus())
        ,m_TestUrl(proxy.TestUrl())
        ,m_pTimeoutTimer(nullptr)
{
    initializeTimer();
}

Proxy::Proxy(const QUuid& proxyId)
    :   QObject()
        ,m_Id(proxyId)
        ,m_Address()
        ,m_UserName()
        ,m_UserPass()
        ,m_Port(0)
        ,m_LastCheck()
        ,m_LastStatus()
        ,m_TestUrl(DEFAULT_TEST_URL)
        ,m_pTimeoutTimer(nullptr)
{
    initializeTimer();
}

Proxy::~Proxy(){}

bool
Proxy::isValid()const
{
    if(m_Address.isEmpty() || m_Port == 0)
        return false;

    return true;
}

Proxy&
Proxy::operator=(const Proxy& proxy)
{
    m_Id = proxy.Id();
    m_Address = proxy.Address();
    m_UserName = proxy.UserName();
    m_UserPass = proxy.UserPass();
    m_Port = proxy.Port();
    m_LastCheck = proxy.LastCheck();
    m_LastStatus = proxy.LastStatus();
    m_TestUrl = proxy.TestUrl();

    return *this;
}

bool
Proxy::operator==(const Proxy& proxy)const
{
    return m_Id == proxy.Id();
}

bool
Proxy::operator!=(const Proxy& proxy)const
{
    return !(this->operator ==(proxy));
}

void
Proxy::initializeTimer()
{
    if(m_pTimeoutTimer == nullptr)
        m_pTimeoutTimer = new QTimer();

    m_pTimeoutTimer->setSingleShot(true);
    m_pTimeoutTimer->setInterval(DEFAULT_PROXY_TIMEOUT);
}
