#include "agent.h"

using namespace Data;

Agent::Agent()
    :   m_Id(QUuid())
        ,m_Alias()
        ,m_BrowserAgent(DEFAULT_BROWSER_AGENT)
{
}

Agent::Agent(const Agent& agent)
    :   m_Id(agent.Id())
        ,m_Alias(agent.Alias())
        ,m_BrowserAgent(agent.BrowserAgent())
{
}

Agent::~Agent(){}

void
Agent::read(const QJsonObject &json)
{
    m_Id = QUuid();
    m_Alias.clear();
    m_BrowserAgent = DEFAULT_BROWSER_AGENT;

    if(json.isEmpty())
        return;

    m_Id = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::AgentId]].toString().toLocal8Bit());
    m_Alias = json[Core::JSonNames[Core::JSonNameIds::AgentAlias]].toString();
    m_BrowserAgent = json[Core::JSonNames[Core::JSonNameIds::AgentAlias]].toString();
}

void
Agent::write(QJsonObject &json)const
{
    json[Core::JSonNames[Core::JSonNameIds::AgentId]] = QString(m_Id.toRfc4122());
    json[Core::JSonNames[Core::JSonNameIds::AgentAlias]] = m_Alias;
    json[Core::JSonNames[Core::JSonNameIds::AgentBrowserAgent]] = m_BrowserAgent;
}

Agent&
Agent::operator=(const Agent& agent)
{
    m_Id = agent.Id();
    m_Alias = agent.Alias();
    m_BrowserAgent = agent.BrowserAgent();

    return *this;
}

bool
Agent::operator==(const Agent& agent)const
{
    return Id().operator ==(agent.Id());
}

bool
Agent::operator!=(const Agent& agent)const
{
    return !(this->operator ==(agent));
}
