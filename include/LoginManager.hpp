#ifndef EXAM_WARE_LOGIN_MANAGER_HPP
#define EXAM_WARE_LOGIN_MANAGER_HPP

#include "User/User.hpp"
#include "UserDataManager.hpp"

class LoginManager
{
public:
    enum LoginState { SUCCESS, USER_NOT_EXISTS, WRONG_PASSWORD };

    static LoginManager &getInstance();

    LoginState login(const User::Username &, const Password &);
    void logout();

    User *getCurrentUser();
    const User *getCurrentUser() const;

    ~LoginManager();

private:
    LoginManager();

    User *user = nullptr;
};

#endif // EXAM_WARE_LOGIN_MANAGER_HPP
