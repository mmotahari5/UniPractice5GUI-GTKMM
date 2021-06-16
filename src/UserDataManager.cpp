#include "UserDataManager.hpp"

#include "User/Student.hpp"
#include "User/Master.hpp"
#include "User/UserSerializer.hpp"
#include "Exception.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

const Path UserDataManager::usersInfoFilePath =
    dirname(__FILE__) + "../data/users-info.txt";
const Path UserDataManager::usersPasswordFilePath =
    dirname(__FILE__) + "../data/users-password.txt";

UserDataManager &UserDataManager::getInstance()
{
    static UserDataManager instance;
    return instance;
}

const User *UserDataManager::select(const User::Username &username)
{
    return this->findUser(username).user;
}

UserDataManager::UserVerificationStatus UserDataManager::selectVerify(
    const User::Username &username,
    const Password &password
) {
    UserCache userCache = this->findUser(username);

    if (!this->verifyPassword(userCache, password)) {
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, userCache.user);
}

void UserDataManager::update(User *user)
{
    ensureIsNotNullptr(user, "User");

    UserCache userCache = this->findUser(user->getUsername());

    LineVector lines = fileGetLines(UserDataManager::usersInfoFilePath);

    lines.at(userCache.recordIndex) = UserSerializer::getInstance().serialize(user);

    filePutLines(UserDataManager::usersInfoFilePath, lines);
}

void UserDataManager::updatePassword(
    User *user,
    const OldPassword &oldPassword,
    const NewPassword &newPassword
) {
    ensureIsNotNullptr(user, "User");

    UserCache userCache = this->findUser(user->getUsername());

    LineVector lines = fileGetLines(UserDataManager::usersPasswordFilePath);

    this->verifyPassword(userCache, oldPassword);

    lines.at(userCache.recordIndex) = this->serializePasswordEntry(
        userCache.user->getUsername(), newPassword
    );

    filePutLines(UserDataManager::usersPasswordFilePath, lines);
}

UserDataManager::Serialized UserDataManager::serializePasswordEntry(
    const User::Username &username,
    const Password &password
) {
    std::stringstream resultStream;

    resultStream << std::left <<
        std::setw(UserSerializer::serializedUsernameSize) << username <<
        std::setw(UserDataManager::passwordSizeLimit) << password;

    return resultStream.str();
}

UserDataManager::UserDataManager()
{}

UserDataManager::UserCache UserDataManager::findUser(const User::Username &username)
{
    auto cacheIt = this->cache.lower_bound(username);

    // If found in cache
    if (cacheIt != this->cache.end() && cacheIt->second.user->getUsername() == username) {
        return cacheIt->second;
    }

    // Else; i.e. not found in cache, so we want to cache it

    Range userSearchRange;

    if (cacheIt != this->cache.end()) {
        userSearchRange.end = cacheIt->second.recordIndex;
        // If the username is the first member of the cache, then we have no lower-bound
        userSearchRange.start = cacheIt == this->cache.begin()
            ? 0 : (--cacheIt)->second.recordIndex;
    }
    // cacheIt == this->cache.end()
    else if (this->cache.size() > 0) {
        userSearchRange.start = 0;
        userSearchRange.end = (--cacheIt)->second.recordIndex;
    }
    // cacheIt == this->cache.end() && this->cache.size() == 0
    else {
        userSearchRange.start = 0;
        userSearchRange.end = this->getInfoFileRecordCount() - 1;
    }

    UserCache userCache = this->findUserInfoFile(username, userSearchRange);

    // Cache it for the next time
    this->cache.insert(cacheIt, {userCache.user->getUsername(), userCache});

    return userCache;
}

UserDataManager::UserCache UserDataManager::findUserInfoFile(
    const User::Username &username,
    Range searchRange
) {
    RecordIndex median = 0;
    std::string buffer;

    std::ifstream file = fileOpen<std::ifstream>(UserDataManager::usersInfoFilePath);

    // Binary search, because the data is sorted
    // If data is found, it will be returned from inside of the loop
    while (true) {
        if (static_cast<int>(searchRange.start) > static_cast<int>(searchRange.end)) {
            // Not found
            break;
        }

        median = (searchRange.start + searchRange.end) / 2;

        User *user = UserSerializer::getInstance().deserialize(
            this->readLineInfoFile(file, median)
        );

        UserCache userCache{median, user};
        this->cache.insert({user->getUsername(), userCache});

        if (username == user->getUsername()) {
            return userCache;
        } else if (username < user->getUsername()) {
            searchRange.end = median - 1;
        } else {
            searchRange.start = median + 1;
        }
    }

    throw UserNotFoundException{};
}

std::string UserDataManager::readLineInfoFile(std::ifstream &file, RecordIndex index)
{
    // + 1: For the new line of each record
    file.seekg(index * (UserSerializer::serializedUserSize + 1));

    std::string result;
    std::getline(file, result);

    return result;
}

size_t UserDataManager::getInfoFileRecordCount() const
{
    return fileSize(UserDataManager::usersInfoFilePath) /
        (UserSerializer::serializedUserSize + 1);
}

bool UserDataManager::verifyPassword(const UserCache &userCache, const Password &password)
{
    return this->getPasswordFor(userCache) == password;
}

Password UserDataManager::getPasswordFor(const UserCache &userCache)
{
    static const size_t passwordFileRecordSize = UserSerializer::serializedUsernameSize
        + UserDataManager::passwordSizeLimit;

    std::ifstream passwordFile =
        fileOpen<std::ifstream>(UserDataManager::usersPasswordFilePath);

    passwordFile.seekg(userCache.recordIndex * (passwordFileRecordSize + 1));

    std::string username, password;
    passwordFile >> username >> password;

    if (userCache.user->getUsername() != username) {
        throw std::logic_error{"Users password and info files are not tied"};
    }

    return password;
}
