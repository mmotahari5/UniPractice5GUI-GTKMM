#include "Exam/ExamStudentAccess.hpp"

ExamStudentAccess::ExamStudentAccess(Exam &exam): ExamAccess(exam)
{}

void ExamStudentAccess::commitAnswerSheet(AnswerSheet answerSheet)
{
    this->exam.commitAnswerSheet(answerSheet);
}

const Question *ExamStudentAccess::getQuestion(const Question::Id &questionId) const
{
    return this->exam.getQuestion(questionId);
}
