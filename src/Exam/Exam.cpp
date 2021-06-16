#include "Exam/Exam.hpp"

#define RANDOM_ID_PREFIX "exam"

Exam::Exam(): id(generateRandomId(RANDOM_ID_PREFIX))
{}

Id Exam::getId() const
{
    return this->id;
}

Exam Exam::clone() const
{
    Exam newExam;

    newExam.criteriaSheet = this->criteriaSheet.clone();

    return newExam;
}

void Exam::addQuestion(Question *question)
{
    this->criteriaSheet.addQuestion(question);
}

void Exam::removeQuestion(const Question::Id &questionId)
{
    this->criteriaSheet.removeQuestion(questionId);
}

Question *Exam::getQuestion(const Question::Id &questionId)
{
    return this->criteriaSheet.getQuestion(questionId);
}

const std::vector<Question *> &Exam::getQuestionList() const
{
    return this->criteriaSheet.getQuestionList();
}

AnswerSheet Exam::startTaking() const
{
    return this->criteriaSheet.copy();
}

void Exam::commitAnswerSheet(AnswerSheet answer)
{
    this->answerSheets.push_back(answer);
}

Question::Score Exam::getMaxScore() const
{
    return this->criteriaSheet.getTotalScore();
}

Question *Exam::operator[](const Question::Id &questionId)
{
    return this->getQuestion(questionId);
}
