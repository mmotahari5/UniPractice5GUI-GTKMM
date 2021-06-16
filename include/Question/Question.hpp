#ifndef EXAM_WARE_QUESTION_HPP
#define EXAM_WARE_QUESTION_HPP

#include "Util.hpp"
#include "Answer/Answer.hpp"

class Question
{
public:
    using Id = ::Id;
    using Text = std::string;
    using Score = float;

    virtual void copy(Question *&) const;
    virtual void clone(Question *&) const = 0;

    Id getId() const;

    virtual Text getText() const;
    Score getScore() const;

    void setText(Text);
    void setScore(Score);

    virtual void setAnswer(const Answer *) = 0;
    virtual Answer *getAnswer() const = 0;
    virtual bool hasAnswer() const = 0;

    virtual std::string toString(bool) const = 0;

    Score operator+(const Question &) const;

    virtual ~Question() = 0;

protected:
    Question(Text, Score);

private:
    friend Score operator+(Score scr, const Question &question);

    Id id;
    Text text;
    Score score;
};

Question::Score operator+(Question::Score, const Question &);

#endif // EXAM_WARE_QUESTION_HPP
