#include "session.h"

using namespace Data;

Session::Session()
    :   m_Id(QUuid::createUuid())
        ,m_Name()
        ,m_Pages()
{
}

Session::Session(const Session& session)
    :   m_Id(session.Id())
        ,m_Name(session.Name())
        ,m_Pages(session.Pages())
{}

Session::~Session(){}

void
Session::addPage(const Data::Page& page)
{
    if(m_Pages.contains(page))
        return;

    m_Pages.append(page);
}

void
Session::remPage(const QUuid& pageId)
{
    m_Pages.removeOne(Data::Page(pageId));
}

Data::Page*
Session::findPage(const QUuid& pageId)
{
    Data::Page* page = nullptr;

    if(pageId.isNull())
        return page;

    for(Data::Page& pageInfo : m_Pages){
        if(pageInfo.Id() == pageId){
            page = &pageInfo;
            break;
        }
    }

    return page;
}

void
Session::read(const QJsonObject &json)
{
    m_Id = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::SessionId]].toString().toLocal8Bit());
    m_Name = json[Core::JSonNames[Core::JSonNameIds::SessionName]].toString();

    QJsonArray jsonPages = json[Core::JSonNames[Core::JSonNameIds::SessionPages]].toArray();
    if(!jsonPages.isEmpty()){
        for(const QJsonValue& jsonPage : jsonPages){
            if(!jsonPage.isObject())
                continue;

            QJsonObject jsonObjectPage = jsonPage.toObject();
            m_Pages.append(Data::Page());
            m_Pages.last().read(jsonObjectPage);
        }
    }
}

void
Session::write(QJsonObject &json)const
{
    json[Core::JSonNames[Core::JSonNameIds::SessionId]] = QString(m_Id.toRfc4122());
    json[Core::JSonNames[Core::JSonNameIds::SessionName]] = m_Name;

    QJsonArray pages;
    for(const Data::Page& pageInfo : m_Pages){
        QJsonObject tempObj;
        pageInfo.write(tempObj);
        pages.append(tempObj);
    }
    json[Core::JSonNames[Core::JSonNameIds::SessionPages]] = pages;
}

Session&
Session::operator=(const Session& session)
{
    m_Id = session.Id();
    m_Name = session.Name();
    m_Pages = session.Pages();

    return *this;
}

bool
Session::operator==(const Session& session)const
{
    return m_Id == session.Id();
}

bool
Session::operator!=(const Session& session)const
{
    return !(this->operator ==(session));
}

