#ifndef EXAM_WARE_TEXTUAL_ANSWER_HPP
#define EXAM_WARE_TEXTUAL_ANSWER_HPP

#include <string>
#include "Answer/Answer.hpp"

class TextualAnswer: public Answer
{
public:
    using Text = std::string;

    TextualAnswer();
    TextualAnswer(Text);

    void set(Text);
    Text get() const;

    virtual void clear();
    virtual operator bool() const;

private:
    Text answerText;
};

#endif // EXAM_WARE_TEXTUAL_ANSWER_HPP
