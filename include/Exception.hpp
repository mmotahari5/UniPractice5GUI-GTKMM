#ifndef EXAM_WARE_EXCEPTION_HPP
#define EXAM_WARE_EXCEPTION_HPP

#include <stdexcept>

class FileOpeningException: public std::runtime_error
{
public:
    FileOpeningException(): std::runtime_error("The file could not be opened")
    {}
};

class UserNotFoundException: public std::runtime_error
{
public:
    UserNotFoundException(): std::runtime_error("User with such a username not found")
    {}
};

class NoLoginException: public std::logic_error
{
public:
    NoLoginException(): std::logic_error("Trying an operation needing an active login")
    {}
};

class AccessDeniedException: public std::runtime_error
{
public:
    AccessDeniedException(): std::runtime_error("Permission denied")
    {}
};

class InvalidOptionException: public std::invalid_argument
{
public:
    InvalidOptionException(): std::invalid_argument("Invalid option passed")
    {}
};

#endif // EXAM_WARE_EXCEPTION_HPP
