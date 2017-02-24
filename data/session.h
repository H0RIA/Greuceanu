/*!
    \legalese

    Copyright 2017 Horia Popa

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following conditions:


    The above copyright notice and this permission notice shall be included in all copies
    or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
    THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    \endlegalese
*/

#ifndef SESSION
#define SESSION

#include "page.h"

namespace Data
{
    class Session : public IJsonInterface
    {
        DECLARE_PROPERTY(QUuid, Id)
        DECLARE_PROPERTY(QString, Name)
        DECLARE_PROPERTY(QList<Data::Page>, Pages)

        public:
            Session();
            Session(const Session& session);
            virtual ~Session();

            void addPage(const Data::Page& page);
            void remPage(const QUuid& pageId);
            Data::Page* findPage(const QUuid& pageId);

            void read(const QJsonObject &json) override;
            void write(QJsonObject &json)const override;

            Session& operator=(const Session& session);
            bool operator==(const Session& session)const;
            bool operator!=(const Session& session)const;
    };
}

#endif // SESSION

