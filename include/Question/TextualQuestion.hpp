#ifndef EXAM_WARE_TEXTUAL_QUESTION_HPP
#define EXAM_WARE_TEXTUAL_QUESTION_HPP

#include "Question/Question.hpp"
#include "Answer/TextualAnswer.hpp"

class TextualQuestion: public Question
{
public:
    TextualQuestion(Text, Score);

    virtual void clone(Question *&) const;

    virtual void setAnswer(const Answer *);
    virtual TextualAnswer *getAnswer() const;
    virtual bool hasAnswer() const;

    virtual std::string toString(bool) const;

    virtual ~TextualQuestion();

private:
    TextualAnswer *answer = nullptr;
};

#endif // EXAM_WARE_TEXTUAL_QUESTION_HPP
