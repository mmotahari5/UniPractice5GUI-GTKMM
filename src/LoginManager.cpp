#include "LoginManager.hpp"

#include "Util.hpp"
#include "User/Master.hpp"
#include "User/Student.hpp"
#include "Exception.hpp"

LoginManager &LoginManager::getInstance()
{
    static LoginManager instance;
    return instance;
}

LoginManager::LoginState LoginManager::login(
    const User::Username &username,
    const Password &password
) {
    UserDataManager::UserVerificationStatus verificationStat;

    try {
				verificationStat = UserDataManager::getInstance().selectVerify(username, password);
    } catch (UserNotFoundException &) {
        return LoginState::USER_NOT_EXISTS;
    }

    // Is password wrong
    if (verificationStat.first == false) {
        return LoginState::WRONG_PASSWORD;
    }

    this->user = verificationStat.second;
    return LoginState::SUCCESS;
}

void LoginManager::logout()
{
    if (this->user == nullptr) {
        throw NoLoginException();
    }

    UserDataManager::getInstance().update(this->user);

    // We should not delete it here, since it was allocated somewhere else
    this->user = nullptr;
}

User *LoginManager::getCurrentUser()
{
    if (this->user == nullptr) {
        throw NoLoginException{};
    }

    return this->user;
}

const User *LoginManager::getCurrentUser() const
{
    if (this->user == nullptr) {
        throw NoLoginException{};
    }

    return this->user;
}

LoginManager::~LoginManager()
{
    try {
        this->logout();
    } catch (NoLoginException &) {}
}

LoginManager::LoginManager()
{}
