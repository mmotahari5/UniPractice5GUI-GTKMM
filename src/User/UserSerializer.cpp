#include "User/UserSerializer.hpp"

#include "User/Master.hpp"
#include "User/Student.hpp"
#include "Util.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

UserSerializer &UserSerializer::getInstance()
{
    static UserSerializer instance;
    return instance;
}

UserSerializer::Serialized UserSerializer::serialize(const User *user) const
{
    ensureIsNotNullptr(user, "User");

    std::stringstream serializedStrStream;

    serializedStrStream << std::left <<
        std::setw(UserSerializer::serializedTypeSize) <<
            UserSerializer::getSerializedType(user) <<
        std::setw(UserSerializer::serializedNameSize) <<
            UserSerializer::getSerializedName(user) <<
        std::setw(UserSerializer::serializedUsernameSize) <<
            UserSerializer::getSerializedUsername(user);

    return serializedStrStream.str();
}

User *UserSerializer::deserialize(const Serialized &serialized)
{
    UserType userType = UserSerializer::getType(serialized);
    User::Name name = UserSerializer::getName(serialized);
    User::Username username = UserSerializer::getUsername(serialized);

    User *user = nullptr;
    switch (userType) {
        case UserType::STUDENT:
            user = new Student{name, username};
            break;

        case UserType::MASTER:
            user = new Master{name, username};
            break;
    }

    this->users.push_back(user);

    return user;
}

char UserSerializer::getSerializedType(const User *user)
{
    if (dynamic_cast<const Student *>(user) != nullptr) {
        return 's';
    } else if (dynamic_cast<const Master *>(user) != nullptr) {
        return 'm';
    }

    throw std::invalid_argument{"User type cannot be detected"};
}

UserSerializer::Serialized UserSerializer::getSerializedName(const User *user)
{
    return '"' + user->getName() + '"';
}

UserSerializer::Serialized UserSerializer::getSerializedUsername(const User *user)
{
    if (user->getUsername().size() > UserSerializer::serializedUsernameSize) {
        throw std::invalid_argument{"Too large username for user"};
    }

    return user->getUsername();
}

UserSerializer::UserType UserSerializer::getType(const Serialized &serialized)
{
    switch (serialized[0]) {
        case 'm':
            return UserType::MASTER;
            // No break

        case 's':
            return UserType::STUDENT;
            // No break

        default:
            throw std::invalid_argument{"Invalid type in the serialized user"};
            // No break
    }
}

User::Name UserSerializer::getName(const Serialized &serialized)
{
    if (std::count(serialized.begin(), serialized.end(), '"') != 2) {
        throw std::invalid_argument{"Wrong serialized user"};
    }

    std::pair<size_t, size_t> namePos;

    namePos.first = serialized.find_first_of('"') + 1;
    namePos.second = serialized.find_first_of('"', namePos.first);

    return serialized.substr(
        namePos.first,
        namePos.second - namePos.first
    );
}

User::Username UserSerializer::getUsername(const Serialized &serialized)
{
    User::Username result = serialized.substr(
        UserSerializer::serializedNameSize + UserSerializer::serializedTypeSize,
        UserSerializer::serializedUsernameSize
    );

    // Right-trimming
    size_t pos;
    if ((pos = result.find(' ')) != std::string::npos) {
        return result.substr(0, pos);
    }

    return result;
}

UserSerializer::UserSerializer()
{}

UserSerializer::~UserSerializer()
{
    for (User *&u: this->users) {
        delete u;
        u = nullptr;
    }
}

