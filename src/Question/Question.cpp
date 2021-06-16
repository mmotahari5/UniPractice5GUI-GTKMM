#include "Question/Question.hpp"

#include "Util.hpp"

#define RANDOM_ID_PREFIX "question"

void Question::copy(Question *&destQuestion) const
{
    this->clone(destQuestion);
    destQuestion->id = this->id;
}

Id Question::getId() const
{
    return this->id;
}

Question::Text Question::getText() const
{
    return this->text;
}

Question::Score Question::getScore() const
{
    return this->score;
}

void Question::setText(Text text)
{
    this->text = text;
}

void Question::setScore(Score score)
{
    if (score < 0.0) {
        throw std::invalid_argument{"Question's score must be non-negative"};
    }

    this->score = score;
}

Question::Score Question::operator+(const Question &q) const
{
    return this->score + q.score;
}

Question::Score operator+(Question::Score score, const Question &question)
{
    return score + question.score;
}

Question::~Question()
{}

Question::Question(Text text, Score score):
    id(generateRandomId(RANDOM_ID_PREFIX)),
    text(text),
    score(score)
{}
