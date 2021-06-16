#include "Answer/FourChoicesAnswer.hpp"

FourChoicesAnswer::FourChoicesAnswer():
    optionNumber(0)
{}

FourChoicesAnswer::FourChoicesAnswer(OptionNumber optionNumber):
    optionNumber(optionNumber)
{}

void FourChoicesAnswer::set(OptionNumber optionNumber)
{
    this->optionNumber = optionNumber;
}

FourChoicesAnswer::OptionNumber FourChoicesAnswer::get() const
{
    return this->optionNumber;
}

void FourChoicesAnswer::clear()
{
    this->optionNumber = 0;
}

FourChoicesAnswer::operator bool() const
{
    return this->optionNumber != 0;
}

bool FourChoicesAnswer::operator==(const FourChoicesAnswer &other) const
{
    return other.optionNumber == this->optionNumber;
}
