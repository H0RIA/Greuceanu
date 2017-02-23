#include <iostream>
#include "proxy.h"

using namespace Data;

std::ostream& operator<< (std::ostream& stream, const Data::ProxyStatus& val)
{
    std::string strValue;

    switch(val)
    {
        case ProxyStatus::Active:
            strValue = "Data::ProxyStatus(Active)";
            break;
        case ProxyStatus::Inactive:
            strValue = "Data::ProxyStatus(Inactive)";
            break;
        case ProxyStatus::Testing:
            strValue = "Data::ProxyStatus(Testing)";
            break;
        case ProxyStatus::Unknown:
            strValue = "Data::ProxyStatus(Unknown)";
            break;
    }

    stream << strValue;

    return stream;
}

Proxy::Proxy(QObject* parent)
    :   QObject(parent)
        ,m_Id(QUuid::createUuid())
        ,m_Address()
        ,m_UserName()
        ,m_UserPass()
        ,m_Port(0)
        ,m_LastCheck()
        ,m_LastStatusDescription()
        ,m_TestUrl(DEFAULT_TEST_URL)
        ,m_pTimeoutTimer(nullptr)
        ,m_LastStatus(ProxyStatus::Unknown)
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
        ,m_LastStatusDescription(proxy.LastStatusDescription())
        ,m_TestUrl(proxy.TestUrl())
        ,m_pTimeoutTimer(nullptr)
        ,m_LastStatus(proxy.LastStatus())
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
        ,m_LastStatusDescription()
        ,m_TestUrl(DEFAULT_TEST_URL)
        ,m_pTimeoutTimer(nullptr)
        ,m_LastStatus()
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

ProxyStatus
Proxy::LastStatus()const
{
    return m_LastStatus;
}

void
Proxy::setLastStatus(ProxyStatus status)
{
    if(m_LastStatus != status){
        m_LastStatus = status;
        if(m_LastStatus != ProxyStatus::Testing)
            emit statusChanged(status);
    }
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
    m_LastStatusDescription = proxy.LastStatusDescription();
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

void
Proxy::printStatus()
{
    std::cerr << "Proxy info: " << m_Address.toLocal8Bit().data() << ":" \
             << m_Port << " -> " << m_LastCheck.toString().toLocal8Bit().data() << " -> " \
             << m_LastStatus << " -> " << m_LastStatusDescription.toLocal8Bit().data() << std::endl;
}
