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
{}

Proxy::Proxy(const Proxy& proxy)
    :   QObject(parent())
        ,m_Id(proxy.Id())
        ,m_Address(proxy.Address())
        ,m_UserName(proxy.UserName())
        ,m_UserPass(proxy.UserPass())
        ,m_Port(proxy.Port())
        ,m_LastCheck(proxy.LastCheck())
        ,m_LastStatus(proxy.LastStatus())
{}

Proxy::~Proxy(){}

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

