#include "User/User.hpp"

User::Name User::getName() const
{
    return this->name;
}

void User::changeName(Name name)
{
    this->name = name;
}

User::Username User::getUsername() const
{
    return this->username;
}

User::~User()
{}

User::User(Name name, Username username):
    name(name),
    username(username)
{}
