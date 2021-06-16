#ifndef EXAM_WARE_STUDENT_HPP
#define EXAM_WARE_STUDENT_HPP

#include "User/User.hpp"

class Student: public User
{
public:
    Student(Name, Username);
    virtual ~Student() = default;
};

#endif // EXAM_WARE_STUDENT_HPP
