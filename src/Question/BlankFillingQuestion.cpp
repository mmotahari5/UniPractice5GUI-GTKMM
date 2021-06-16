#include "Question/BlankFillingQuestion.hpp"

BlankFillingQuestion::BlankFillingQuestion(Text text, Placeholder placeholder, Score score):
    Question(text, score),
    placeholder(placeholder),
    answer(new BlankFillingAnswer{})
{
    this->ensurePlaceholderExists(text, placeholder);
}

void BlankFillingQuestion::setText(Text text, Placeholder placeholder)
{
    this->ensurePlaceholderExists(text, placeholder);

    Question::setText(text);
    this->placeholder = placeholder;
}

Question::Text BlankFillingQuestion::getText() const
{
    Text result = Question::getText();
    const Text replacement(this->placeholder.size(), '_');

    return result.replace(
        result.find(this->placeholder), replacement.size(), replacement
    );
}

void BlankFillingQuestion::clone(Question *&destQuestion) const
{
    ensureIsNullptr(destQuestion, "Question");

    BlankFillingQuestion *q = new BlankFillingQuestion(
        Question::getText(), this->placeholder, this->getScore()
    );

    q->answer->set(this->answer->get());

    destQuestion = q;
}

void BlankFillingQuestion::setAnswer(const Answer *answer)
{
    const BlankFillingAnswer *blankFillingAnswer =
        dynamic_cast<const BlankFillingAnswer *>(answer);

    if (blankFillingAnswer == nullptr) {
        throw std::invalid_argument{"Answer must be of type BlankFillingAnswer"};
    }

    this->answer->set(blankFillingAnswer->get());
}

BlankFillingAnswer *BlankFillingQuestion::getAnswer() const
{
    return this->answer;
}

bool BlankFillingQuestion::hasAnswer() const
{
    return this->answer;
}

std::string BlankFillingQuestion::toString(bool includeAnswer) const
{
    std::string result{this->getText() + NEW_LINE};

    if (includeAnswer) {
        result += NEW_LINE;
        result += "Given answer:" NEW_LINE;
        result += this->answer->get() + NEW_LINE;
    }

    return result;
}

BlankFillingQuestion::~BlankFillingQuestion()
{
    delete this->answer;
}

void BlankFillingQuestion::ensurePlaceholderExists(Text text, Placeholder placeholder)
{
    size_t placeholderPosition = text.find(placeholder);
    if (placeholderPosition == std::string::npos) {
        throw std::invalid_argument{
            "Placeholder must appear at least one time in question text"
        };
    }
}
