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
    m_Id = QUuid(json[Core::JSonNames[Core::JSonNameIds::PageId]].toString());
    m_Name = json[Core::JSonNames[Core::JSonNameIds::PageName]].toString();
    m_Url = json[Core::JSonNames[Core::JSonNameIds::PageUrl]].toString();
    m_ProxyId = QUuid(json[Core::JSonNames[Core::JSonNameIds::PageProxyId]].toString());
    m_ProxyEnabled = json[Core::JSonNames[Core::JSonNameIds::PageProxyEnabled]].toBool();
    m_AgentId = QUuid(json[Core::JSonNames[Core::JSonNameIds::PageAgentId]].toString());
    m_SessionId = QUuid(json[Core::JSonNames[Core::JSonNameIds::PageSessionId]].toString());
}

void
Page::write(QJsonObject &json)const
{
    json[Core::JSonNames[Core::JSonNameIds::PageId]] = m_Id.toString();
    json[Core::JSonNames[Core::JSonNameIds::PageName]] = m_Name;
    json[Core::JSonNames[Core::JSonNameIds::PageUrl]] = m_Url;
    json[Core::JSonNames[Core::JSonNameIds::PageProxyId]] = m_ProxyId.toString();
    json[Core::JSonNames[Core::JSonNameIds::PageProxyEnabled]] = m_ProxyEnabled;
    json[Core::JSonNames[Core::JSonNameIds::PageAgentId]] = m_AgentId.toString();
    json[Core::JSonNames[Core::JSonNameIds::PageSessionId]] = m_SessionId.toString();
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

