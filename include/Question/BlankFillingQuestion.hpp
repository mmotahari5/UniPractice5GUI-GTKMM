#ifndef EXAM_WARE_BLANK_FILLING_QUESTION_HPP
#define EXAM_WARE_BLANK_FILLING_QUESTION_HPP

#include "Question/Question.hpp"
#include "Answer/BlankFillingAnswer.hpp"

class BlankFillingQuestion: public Question
{
public:
    using Placeholder = std::string;

    BlankFillingQuestion(Text, Placeholder, Score);

    void setText(Question::Text, Placeholder);
    virtual Question::Text getText() const;

    virtual void clone(Question *&) const;

    virtual void setAnswer(const Answer *);
    virtual BlankFillingAnswer *getAnswer() const;
    virtual bool hasAnswer() const;

    virtual std::string toString(bool) const;

    virtual ~BlankFillingQuestion();

private:
    using Question::setText;

    static void ensurePlaceholderExists(Text, Placeholder);

    Placeholder placeholder;
    BlankFillingAnswer *answer;
};

#endif // EXAM_WARE_BLANK_FILLING_QUESTION_HPP
