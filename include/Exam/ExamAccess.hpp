#ifndef EXAM_WARE_EXAM_ACCESS_HPP
#define EXAM_WARE_EXAM_ACCESS_HPP

#include "Exam/Exam.hpp"

class ExamAccess
{
public:
    Exam::Id getId() const;

    AnswerSheet startTaking() const;
    const std::vector<Question *> &getQuestionList() const;
    Question::Score getMaxScore() const;

    Exam clone() const;

    const Question *operator[](const Question::Id &) const;

    // Only to make the class abstract
    virtual ~ExamAccess() = 0;

protected:
    ExamAccess(Exam &);

    Exam &exam;
};

#endif // EXAM_WARE_EXAM_ACCESS_HPP
