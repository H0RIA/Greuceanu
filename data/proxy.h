# Copyright 2017 Horia Popa
# https://github.com/H0RIA
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this
# software and associated documentation files (the "Software"), to deal in the Software
# without restriction, including without limitation the rights to use, copy, modify,
# merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies
# or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
# BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
# THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

#ifndef PROXY
#define PROXY

#include "base.h"

namespace Data
{
    enum class ProxyStatus
    {
        Active,     // Last test ran succeeded
        Inactive,   // Last test ran failed
        Pending,    // Running the tests on the proxy
        Unknown     // No tests were ran
    };

    class Proxy : public QObject
    {
        Q_OBJECT

        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, Address)
        DECLARE_PROPERTY(QString, UserName)
        DECLARE_PROPERTY(QString, UserPass)
        DECLARE_PROPERTY(int, Port)
        DECLARE_PROPERTY(QDateTime, LastCheck)
        DECLARE_PROPERTY(ProxyStatus, LastStatus)

        public:
            Proxy(QObject* parent = nullptr);
            Proxy(const Proxy& proxy);
            virtual ~Proxy();

            Proxy& operator=(const Proxy& proxy);
            bool operator==(const Proxy& proxy)const;
            bool operator!=(const Proxy& proxy)const;
    };
}

#endif // PROXY

