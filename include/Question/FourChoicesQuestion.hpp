#ifndef EXAM_WARE_FOUR_CHOICES_QUESTION_HPP
#define EXAM_WARE_FOUR_CHOICES_QUESTION_HPP

#include <array>
#include "Question/Question.hpp"
#include "Answer/FourChoicesAnswer.hpp"

class FourChoicesQuestion: public Question
{
public:
    using OptionText = std::string;
    using Options = std::array<OptionText, 4>;

    FourChoicesQuestion(Text, Score, Options);

    const Options &getOptions() const;
    void setOption(size_t, OptionText);

    virtual void clone(Question *&) const;

    virtual void setAnswer(const Answer *);
    virtual FourChoicesAnswer *getAnswer() const;
    virtual bool hasAnswer() const;

    virtual std::string toString(bool) const;

    virtual ~FourChoicesQuestion();

private:
    Options options;
    FourChoicesAnswer *answer = nullptr;
};

#endif // EXAM_WARE_FOUR_CHOICES_QUESTION_HPP
