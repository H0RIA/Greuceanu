#include "agent.h"

using namespace Data;

Agent::Agent()
    :   m_Id(QUuid())
        ,m_Alias()
        ,m_BrowserAgent()
{
}

Agent::Agent(const Agent& agent)
    :   m_Id(agent.Id())
        ,m_Alias(agent.Alias())
        ,m_BrowserAgent(agent.BrowserAgent())
{
}

Agent::~Agent(){}

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
