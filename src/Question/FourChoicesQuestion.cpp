#include "Question/FourChoicesQuestion.hpp"

#include "Util.hpp"

FourChoicesQuestion::FourChoicesQuestion(Text text, Score score, Options options):
    Question(text, score),
    options(options),
    answer(new FourChoicesAnswer{})
{}

void FourChoicesQuestion::setOption(size_t which, OptionText optionText)
{
    options.at(which) = optionText;
}

const FourChoicesQuestion::Options &FourChoicesQuestion::getOptions() const
{
    return this->options;
}

void FourChoicesQuestion::clone(Question *&destQuestion) const
{
    ensureIsNullptr(destQuestion, "Question");

    FourChoicesQuestion *q = new FourChoicesQuestion(
        this->getText(), this->getScore(), this->options
    );

    q->answer->set(this->answer->get());

    destQuestion = q;
}

void FourChoicesQuestion::setAnswer(const Answer *answer)
{
    const FourChoicesAnswer *fourChoicesAnswer =
        dynamic_cast<const FourChoicesAnswer *>(answer);

    if (fourChoicesAnswer == nullptr) {
        throw std::invalid_argument{"Answer must be of type FourChoicesAnswer"};
    }

    this->answer->set(fourChoicesAnswer->get());
}

FourChoicesAnswer *FourChoicesQuestion::getAnswer() const
{
    return this->answer;
}

bool FourChoicesQuestion::hasAnswer() const
{
    return this->answer;
}

std::string FourChoicesQuestion::toString(bool includeAnswer) const
{
    std::string result{this->getText() + NEW_LINE};

    for (size_t i = 0; i < 4; i++) {
        result += std::to_string(i) + ") " + this->options[i] + NEW_LINE;
    }

    if (includeAnswer) {
        result += NEW_LINE;
        result += "Given answer:" NEW_LINE;
        result += std::to_string(this->answer->get()) + NEW_LINE;
    }

    return result;
}

FourChoicesQuestion::~FourChoicesQuestion()
{
    delete this->answer;
}
