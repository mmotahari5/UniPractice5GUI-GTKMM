#include "Exam/ExamAccess.hpp"

ExamAccess::ExamAccess(Exam &exam): exam(exam)
{}

AnswerSheet ExamAccess::startTaking() const
{
    return this->exam.startTaking();
}

const std::vector<Question *> &ExamAccess::getQuestionList() const
{
    return this->exam.getQuestionList();
}

Question::Score ExamAccess::getMaxScore() const
{
    return this->exam.getMaxScore();
}

const Question *ExamAccess::operator[](const Question::Id &questionId) const
{
    return this->exam.operator[](questionId);
}

Exam ExamAccess::clone() const
{
    return this->exam.clone();
}

ExamAccess::~ExamAccess()
{}
