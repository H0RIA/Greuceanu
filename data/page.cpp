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

Page::~Page()
{
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

