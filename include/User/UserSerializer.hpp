#ifndef EXAM_WARE_USER_SERIALIZER_HPP
#define EXAM_WARE_USER_SERIALIZER_HPP

#include "User.hpp"
#include "Master.hpp"
#include <vector>

class UserSerializer
{
public:
    enum UserType { MASTER, STUDENT };
    using Password = std::string;
    using Serialized = std::string;

    static const size_t serializedTypeSize = 2;
    static const size_t serializedNameSize = 40;
    static const size_t serializedUsernameSize = 20;

    static const size_t serializedUserSize =
        UserSerializer::serializedTypeSize +
        UserSerializer::serializedNameSize +
        UserSerializer::serializedUsernameSize;

    static UserSerializer &getInstance();

    Serialized serialize(const User *) const;
    User *deserialize(const Serialized &);

		
    static UserType getType(const Serialized &);

private:

    static char getSerializedType(const User *);
    static Serialized getSerializedName(const User *);
    static Serialized getSerializedUsername(const User *);

    static User::Name getName(const Serialized &);
    static User::Username getUsername(const Serialized &);

    UserSerializer();
    ~UserSerializer();

    /*
     * Again, because std::unique_ptr is not an option. Generally this is a memory leak, as
     * we're keeping unused memory just until the end of the program.
     */
    std::vector<User *> users;
};

#endif // EXAM_WARE_USER_SERIALIZER_HPP
