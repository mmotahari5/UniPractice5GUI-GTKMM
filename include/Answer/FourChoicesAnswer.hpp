#ifndef EXAM_WARE_FOUR_CHOICES_ANSWER_HPP
#define EXAM_WARE_FOUR_CHOICES_ANSWER_HPP

#include <string>
#include "Answer/Answer.hpp"

class FourChoicesAnswer: public Answer
{
public:
    using OptionNumber = size_t;

    FourChoicesAnswer();
    FourChoicesAnswer(OptionNumber);

    void set(OptionNumber);
    OptionNumber get() const;

    bool operator==(const FourChoicesAnswer &) const;

    virtual void clear();
    virtual operator bool() const;

private:
    size_t optionNumber;
};

#endif // EXAM_WARE_FOUR_CHOICES_ANSWER_HPP
