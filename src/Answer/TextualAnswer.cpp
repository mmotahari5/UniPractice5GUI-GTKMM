#include "Answer/TextualAnswer.hpp"

TextualAnswer::TextualAnswer():
    answerText("")
{}

TextualAnswer::TextualAnswer(Text answerText):
    answerText(answerText)
{}

void TextualAnswer::set(Text answerText)
{
    this->answerText = answerText;
}

TextualAnswer::Text TextualAnswer::get() const
{
    return this->answerText;
}

void TextualAnswer::clear()
{
    this->answerText.clear();
}

TextualAnswer::operator bool() const
{
    return !this->answerText.empty();
}
