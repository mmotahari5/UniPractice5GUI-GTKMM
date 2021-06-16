#include "Answer/BlankFillingAnswer.hpp"

BlankFillingAnswer::BlankFillingAnswer():
    answerText("")
{}

BlankFillingAnswer::BlankFillingAnswer(Text answerText):
    answerText(answerText)
{}

void BlankFillingAnswer::set(Text answerText)
{
    this->answerText = answerText;
}

BlankFillingAnswer::Text BlankFillingAnswer::get() const
{
    return this->answerText;
}

void BlankFillingAnswer::clear()
{
    this->answerText.clear();
}

BlankFillingAnswer::operator bool() const
{
    return !this->answerText.empty();
}
