#ifndef EXAM_WARE_USER_DATA_MANAGER_HPP
#define EXAM_WARE_USER_DATA_MANAGER_HPP

#include "Util.hpp"
#include "User/User.hpp"
#include <fstream>
#include <map>

class UserDataManager
{
public:
    using OldPassword = Password;
    using NewPassword = Password;

    using PasswordCorrect = bool;

    using UserVerificationStatus = std::pair<PasswordCorrect, User *>;

    static UserDataManager &getInstance();

    const User *select(const User::Username &);
    UserVerificationStatus selectVerify(const User::Username &, const Password &);

    void update(User *);
    void updatePassword(User *, const OldPassword &, const NewPassword &);

private:
    using Path = std::string;
    using RecordIndex = size_t;
    using Serialized = std::string;

    struct UserCache
    {
        RecordIndex recordIndex;
        User *user;
    };

    struct Range
    {
        RecordIndex start, end;
    };

    static const size_t passwordSizeLimit = 50;

    static const Path usersInfoFilePath;
    static const Path usersPasswordFilePath;

    static Serialized serializePasswordEntry(const User::Username &, const Password &);

    UserDataManager();

    UserCache findUser(const User::Username &);

    UserCache findUserInfoFile(const User::Username &, Range);
    std::string readLineInfoFile(std::ifstream &, RecordIndex);
    size_t getInfoFileRecordCount() const;

    bool verifyPassword(const UserCache &, const Password &);
    Password getPasswordFor(const UserCache &);

    /*
     * When we search for a user in a file, we hit (and try) some users that their username
     * does not match the requested one, but still its data is fetched. Instead of removing
     * the data, we can keep it in memory, so chances are the next requests for usernames
     * will be already in memory (and we hit them). So, every username search first tries
     * the cache, and if not available, it will (binary) search through the file.
     */
    std::map<User::Username, UserCache> cache;
};

#endif // EXAM_WARE_USER_DATA_MANAGER_HPP
