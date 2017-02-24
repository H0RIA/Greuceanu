#include "page.h"

using namespace Data;

Page::Page()
    :   m_Id(QUuid::createUuid())
        ,m_Name()
        ,m_Url()
        ,m_ProxyId()
        ,m_ProxyEnabled(false)
        ,m_AgentId()
        ,m_SessionId()
{
}

Page::Page(const QUuid& id)
    :   m_Id(id)
        ,m_Name()
        ,m_Url()
        ,m_ProxyId()
        ,m_ProxyEnabled(false)
        ,m_AgentId()
        ,m_SessionId()
{
}

Page::Page(const Page& page)
    :   m_Id(page.Id())
        ,m_Name(page.Name())
        ,m_Url(page.Url())
        ,m_ProxyId(page.ProxyId())
        ,m_ProxyEnabled(page.ProxyEnabled())
        ,m_AgentId(page.AgentId())
        ,m_SessionId(page.SessionId())
{
}

Page::~Page(){}

void
Page::read(const QJsonObject &json)
{
    m_Id = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::PageId]].toString().toLocal8Bit());
    m_Name = json[Core::JSonNames[Core::JSonNameIds::PageName]].toString();
    m_Url = json[Core::JSonNames[Core::JSonNameIds::PageUrl]].toString();
    m_ProxyId = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::PageProxyId]].toString().toLocal8Bit());
    m_ProxyEnabled = json[Core::JSonNames[Core::JSonNameIds::PageProxyEnabled]].toBool();
    m_AgentId = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::PageAgentId]].toString().toLocal8Bit());
    m_SessionId = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::PageSessionId]].toString().toLocal8Bit());
}

void
Page::write(QJsonObject &json)const
{
    json[Core::JSonNames[Core::JSonNameIds::PageId]] = QString(m_Id.toRfc4122());
    json[Core::JSonNames[Core::JSonNameIds::PageName]] = m_Name;
    json[Core::JSonNames[Core::JSonNameIds::PageUrl]] = m_Url;
    json[Core::JSonNames[Core::JSonNameIds::PageProxyId]] = QString(m_ProxyId.toRfc4122());
    json[Core::JSonNames[Core::JSonNameIds::PageProxyEnabled]] = m_ProxyEnabled;
    json[Core::JSonNames[Core::JSonNameIds::PageAgentId]] = QString(m_AgentId.toRfc4122());
    json[Core::JSonNames[Core::JSonNameIds::PageSessionId]] = QString(m_SessionId.toRfc4122());
}

Page&
Page::operator=(const Page& page)
{
    m_Id = page.Id();
    m_Name = page.Name();
    m_Url = page.Url();
    m_ProxyId = page.ProxyId();
    m_ProxyEnabled = page.ProxyEnabled();
    m_AgentId = page.AgentId();
    m_SessionId = page.SessionId();

    return *this;
}

bool
Page::operator==(const Page& page)const
{
    return m_Id == page.Id();
}

bool
Page::operator!=(const Page& page)const
{
    return !(this->operator ==(page));
}

