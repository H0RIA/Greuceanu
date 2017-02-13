#ifndef AGENT
#define AGENT

#include "base.h"

namespace Data
{
    class Agent
    {
        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, Alias)
        DECLARE_PROPERTY(QString, BrowserAgent)

        public:
            Agent();
            Agent(const Agent& agent);
            virtual ~Agent();

            Agent& operator=(const Agent& agent);
            bool operator==(const Agent& agent)const;
            bool operator!=(const Agent& agent)const;
    };
}

#endif // AGENT

