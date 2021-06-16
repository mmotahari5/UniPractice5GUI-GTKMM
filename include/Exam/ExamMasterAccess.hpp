#ifndef EXAM_WARE_EXAM_MASTER_ACCESS_HPP
#define EXAM_WARE_EXAM_MASTER_ACCESS_HPP

#include "Exam/ExamAccess.hpp"

class ExamMasterAccess: public ExamAccess
{
public:
    ExamMasterAccess(Exam &);

    void addQuestion(Question *);
    void removeQuestion(const Question::Id &);
    Question *getQuestion(const Question::Id &);
};

#endif // EXAM_WARE_EXAM_MASTER_ACCESS_HPP
