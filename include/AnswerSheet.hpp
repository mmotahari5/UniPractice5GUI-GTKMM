#ifndef EXAM_WARE_ANSWER_SHEET_HPP
#define EXAM_WARE_ANSWER_SHEET_HPP

#include "Question/Question.hpp"

class AnswerSheet
{
public:
    AnswerSheet();
    AnswerSheet(const AnswerSheet &);

    AnswerSheet &operator=(const AnswerSheet &);

    AnswerSheet copy() const;
    AnswerSheet clone() const;

    void addQuestion(const Question *);
    void removeQuestion(const Question::Id &);

    Question *getQuestion(const Question::Id &);

    const std::vector<Question *> &getQuestionList() const;

    Question::Score getTotalScore() const;

    ~AnswerSheet();

private:
    int searchQuestion(const Question::Id &questionId) const;

    void deallocateQuestion(Question *&) noexcept;

    std::vector<Question *> questions;
};

#endif // EXAM_WARE_ANSWER_SHEET_HPP
