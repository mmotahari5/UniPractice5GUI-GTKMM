#include "Exam/ExamMasterAccess.hpp"

ExamMasterAccess::ExamMasterAccess(Exam &exam): ExamAccess(exam)
{}

void ExamMasterAccess::addQuestion(Question *question)
{
    this->exam.addQuestion(question);
}

void ExamMasterAccess::removeQuestion(const Question::Id &questionId)
{
    this->exam.removeQuestion(questionId);
}

Question *ExamMasterAccess::getQuestion(const Question::Id &questionId)
{
    return this->exam.getQuestion(questionId);
}
