#ifndef EXAM_WARE_COURSE_HPP
#define EXAM_WARE_COURSE_HPP

#include "Exam/ExamAccess.hpp"
#include "LoginManager.hpp"
#include "User/Master.hpp"
#include "User/Student.hpp"
#include <vector>

class Course
{
public:
    using Name = std::string;

    Course(Name, Master::Username);

    Name getName() const;
    void setName(Name);

    void addExam(const LoginManager &, Exam);
    void removeExam(const LoginManager &, const Exam::Id &);

    ExamAccess *getExam(const LoginManager &, const Exam::Id &);

    const std::vector<Exam> &getExamList(const LoginManager &) const;

    void changeMaster(const LoginManager &, Master::Username &);

    void registerStudent(const LoginManager &, const Student::Username &);
    void removeStudent(const LoginManager &, const Student::Username &);
    bool isStudentRegistered(const LoginManager &, const Student::Username &) const;

    bool isRegisteredMaster(const LoginManager &) const;

    ~Course();

private:
    int searchExam(const Exam::Id &) const;
    int searchStudent(const Student::Username &) const;

    bool isRegisteredStudent(const LoginManager &) const;

    void assertIsRegisteredMaster(const LoginManager &) const;
    void assertIsRegisteredMasterOrStudent(const LoginManager &) const;

    Name name;
    std::vector<Exam> exams;

    Master::Username masterUsername;
    std::vector<Student::Username> studentUsernames;

    /*
     * Probably not a good idea to keep every instance of ExamAccess children classes, but
     * for better memory management, it is needed (as we cannot force the use of smart
     * pointer, like std::unique_ptr). It is kept here for deletion only. Ideally, there
     * should not be many of these classes created.
     */
    std::vector<ExamAccess *> examAccesses;
};

#endif // EXAM_WARE_COURSE_HPP
