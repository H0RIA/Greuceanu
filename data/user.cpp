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
