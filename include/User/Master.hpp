#ifndef EXAM_WARE_MASTER_HPP
#define EXAM_WARE_MASTER_HPP

#include "User/User.hpp"

class Master: public User
{
public:
    Master(Name, Username);
    virtual ~Master() = default;
};

#endif // EXAM_WARE_MASTER_HPP
