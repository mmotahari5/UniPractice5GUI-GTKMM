#ifndef EXAM_WARE_USER_HPP
#define EXAM_WARE_USER_HPP

#include <string>

class UserSerializer;

class User
{
    friend class UserSerializer;

public:
    using Name = std::string;
    using Username = std::string;

    User(const User &) = delete;

    Name getName() const;
    void changeName(Name);
    Username getUsername() const;

    // Only to make the class abstract
    virtual ~User() = 0;

protected:
    User(Name, Username);

private:
    Name name;
    Username username;
};

#endif // EXAM_WARE_USER_HPP
