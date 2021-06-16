#include "AnswerSheet.hpp"

#include "Util.hpp"
#include "Question/BlankFillingQuestion.hpp"
#include "Question/FourChoicesQuestion.hpp"
#include "Question/TextualQuestion.hpp"

AnswerSheet::AnswerSheet()
{}

AnswerSheet::AnswerSheet(const AnswerSheet &other)
{
    this->operator=(other);
}

AnswerSheet &AnswerSheet::operator=(const AnswerSheet &other)
{
    this->~AnswerSheet();
    this->questions.clear();
    this->questions.reserve(other.questions.size());

    for (const Question *q : other.questions) {
        Question *questionCopy = nullptr;
        q->copy(questionCopy);

        this->questions.push_back(questionCopy);
    }

    return *this;
}

AnswerSheet AnswerSheet::copy() const
{
    AnswerSheet newAnswerSheet{*this};

    for (Question *q : newAnswerSheet.questions) {
        q->getAnswer()->clear();
        q->setScore(0.0f);
    }

    return newAnswerSheet;
}

AnswerSheet AnswerSheet::clone() const
{
    AnswerSheet newAnswerSheet;

    newAnswerSheet.questions.reserve(this->questions.size());

    for (const Question *q : newAnswerSheet.questions) {
        Question *newQuestion = nullptr;
        q->clone(newQuestion);
        newAnswerSheet.questions.push_back(newQuestion);
    }

    return newAnswerSheet;
}

void AnswerSheet::addQuestion(const Question *question)
{
    ensureIsNotNullptr(question, "Question");

    if (this->searchQuestion(question->getId()) != -1) {
        throw std::invalid_argument{"A Question with the same Id exists"};
    }

    Question *questionCopy = nullptr;
    question->copy(questionCopy);
    this->questions.push_back(questionCopy);
}

void AnswerSheet::removeQuestion(const Question::Id &questionId)
{
    int questionIndex = this->searchQuestion(questionId);

    if (questionIndex == -1) {
        throw std::invalid_argument{"Question with such an Id does not exist"};
    }

    this->deallocateQuestion(this->questions[questionIndex]);
    this->questions.erase(questions.begin() + questionIndex);
}

Question *AnswerSheet::getQuestion(const Question::Id &questionId)
{
    int questionIndex = this->searchQuestion(questionId);

    if (questionIndex == -1) {
        throw std::invalid_argument{"Question with such an Id does not exist"};
    }

    return this->questions[questionIndex];
}

const std::vector<Question *> &AnswerSheet::getQuestionList() const
{
    return this->questions;
}

Question::Score AnswerSheet::getTotalScore() const
{
    Question::Score sum = 0;
    for (const Question *q : questions) {
        sum = sum + (*q);
    }

    return sum;
}

AnswerSheet::~AnswerSheet()
{
    for (Question *q : this->questions) {
        this->deallocateQuestion(q);
    }
}

int AnswerSheet::searchQuestion(const Question::Id &questionId) const
{
    for (size_t i = 0; i < questions.size(); i++) {
        if (questions[i]->getId() == questionId) {
            return i;
        }
    }

    return -1;
}

void AnswerSheet::deallocateQuestion(Question *&question) noexcept
{
    delete question;
    question = nullptr;
}
