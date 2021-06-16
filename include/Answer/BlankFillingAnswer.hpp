#ifndef EXAM_WARE_BLANK_FILLING_ANSWER_HPP
#define EXAM_WARE_BLANK_FILLING_ANSWER_HPP

#include <string>
#include "Answer/Answer.hpp"

class BlankFillingAnswer: public Answer
{
public:
    using Text = std::string;

    BlankFillingAnswer();
    BlankFillingAnswer(Text);

    void set(Text);
    Text get() const;

    virtual void clear();
    virtual operator bool() const;

private:
    Text answerText;
};

#endif // EXAM_WARE_BLANK_FILLING_ANSWER_HPP
