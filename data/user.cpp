#include "user.h"

using namespace Data;

User::User()
    :   m_Id(QUuid())
        ,m_UName()
        ,m_Password()
        ,m_FirstName()
        ,m_LastName()
{
}

User::User(const User& user)
    :   m_Id(user.Id())
        ,m_UName(user.UName())
        ,m_Password(user.Password())
        ,m_FirstName(user.FirstName())
        ,m_LastName(user.LastName())
{
}

User::~User(){}

void
User::read(const QJsonObject &json)
{
    m_Id = QUuid::fromRfc4122(json[Core::JSonNames[Core::JSonNameIds::UserId]].toString().toLocal8Bit());
    m_UName = json[Core::JSonNames[Core::JSonNameIds::UserName]].toString();
    m_Password = json[Core::JSonNames[Core::JSonNameIds::UserPassword]].toString();
    m_FirstName = json[Core::JSonNames[Core::JSonNameIds::UserFirstName]].toString();
    m_LastName = json[Core::JSonNames[Core::JSonNameIds::UserLastName]].toString();
}

void
User::write(QJsonObject &json)const
{
    json[Core::JSonNames[Core::JSonNameIds::UserId]] = QString(m_Id.toRfc4122());
    json[Core::JSonNames[Core::JSonNameIds::UserName]] = m_UName;
    json[Core::JSonNames[Core::JSonNameIds::UserPassword]] = m_Password;
    json[Core::JSonNames[Core::JSonNameIds::UserFirstName]] = m_FirstName;
    json[Core::JSonNames[Core::JSonNameIds::UserLastName]] = m_LastName;
}

User&
User::operator=(const User& user)
{
    m_Id = user.Id();
    m_UName = user.UName();
    m_Password = user.Password();
    m_FirstName = user.FirstName();
    m_LastName = user.LastName();

    return *this;
}

bool
User::operator==(const User& user)const
{
    return m_Id.operator ==(user.Id());
}

bool
User::operator!=(const User& user)const
{
    return !(this->operator ==(user));
}
