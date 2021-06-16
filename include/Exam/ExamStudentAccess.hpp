#ifndef EXAM_WARE_EXAM_STUDENT_ACCESS_HPP
#define EXAM_WARE_EXAM_STUDENT_ACCESS_HPP

#include "Exam/ExamAccess.hpp"

class ExamStudentAccess: public ExamAccess
{
public:
    ExamStudentAccess(Exam &);

    void commitAnswerSheet(AnswerSheet);

    const Question *getQuestion(const Question::Id &) const;
};

#endif // EXAM_WARE_EXAM_STUDENT_ACCESS_HPP
