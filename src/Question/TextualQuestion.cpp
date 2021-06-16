#include "Question/TextualQuestion.hpp"

TextualQuestion::TextualQuestion(Text text, Score score):
    Question(text, score),
    answer(new TextualAnswer{})
{}

void TextualQuestion::clone(Question *&destQuestion) const
{
    ensureIsNullptr(destQuestion, "Question");

    TextualQuestion *q = new TextualQuestion(
        this->getText(), this->getScore()
    );

    q->answer->set(this->answer->get());

    destQuestion = q;
}

void TextualQuestion::setAnswer(const Answer *answer)
{
    const TextualAnswer *textualAnswer =
        dynamic_cast<const TextualAnswer *>(answer);

    if (textualAnswer == nullptr) {
        throw std::invalid_argument{"Answer must be of type TextualAnswer"};
    }

    this->answer->set(textualAnswer->get());
}

TextualAnswer *TextualQuestion::getAnswer() const
{
    return this->answer;
}

bool TextualQuestion::hasAnswer() const
{
    return this->answer;
}

std::string TextualQuestion::toString(bool includeAnswer) const
{
    std::string result{this->getText() + NEW_LINE};

    std::string temp = getText();

    if (includeAnswer) {
        result += NEW_LINE;
        result += "Given answer:" NEW_LINE;
        result += this->answer->get() + NEW_LINE;
    }

    return result;
}

TextualQuestion::~TextualQuestion()
{
    delete this->answer;
}
