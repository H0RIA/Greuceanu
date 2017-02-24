#include "base.h"

using namespace Core;

void
Core::initializeJSonNames()
{
    Core::JSonNames[JSonNameIds::AgentId] = "agent_id";
    Core::JSonNames[JSonNameIds::AgentAlias] = "agent_alias";
    Core::JSonNames[JSonNameIds::AgentBrowserAgent] = "agent_browserAgent";

    Core::JSonNames[JSonNameIds::ProxyId] = "proxy_id";
    Core::JSonNames[JSonNameIds::ProxyAddress] = "proxy_address";
    Core::JSonNames[JSonNameIds::ProxyUserName] = "proxy_username";
    Core::JSonNames[JSonNameIds::ProxyUserPass] = "proxy_userpass";
    Core::JSonNames[JSonNameIds::ProxyPort] = "proxy_port";
    Core::JSonNames[JSonNameIds::PorxyLastChecked] = "proxy_lastCheck";
    Core::JSonNames[JSonNameIds::ProxyLastStatus] = "proxy_lastStatus";
    Core::JSonNames[JSonNameIds::ProxyLastStatusDescription] = "proxy_lastStatusDescrition";
    Core::JSonNames[JSonNameIds::ProxyTestUrl] = "proxy_testUrl";

    Core::JSonNames[JSonNameIds::UserId] = "user_id";
    Core::JSonNames[JSonNameIds::UserName] = "user_name";
    Core::JSonNames[JSonNameIds::UserPassword] = "user_pass";
    Core::JSonNames[JSonNameIds::UserFirstName] = "user_firstName";
    Core::JSonNames[JSonNameIds::UserLastName] = "user_lastName";

    Core::JSonNames[JSonNameIds::PageId] = "page_id";
    Core::JSonNames[JSonNameIds::PageName] = "page_name";
    Core::JSonNames[JSonNameIds::PageUrl] = "page_url";
    Core::JSonNames[JSonNameIds::PageProxyId] = "page_proxyId";
    Core::JSonNames[JSonNameIds::PageProxyEnabled] = "page_proxyEnabled";
    Core::JSonNames[JSonNameIds::PageAgentId] = "page_agentId";
    Core::JSonNames[JSonNameIds::PageSessionId] = "page_sessionId";

    Core::JSonNames[JSonNameIds::SessionId] = "session_id";
    Core::JSonNames[JSonNameIds::SessionId] = "session_id";
    Core::JSonNames[JSonNameIds::SessionId] = "session_id";
}
