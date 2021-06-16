#ifndef EXAM_WARE_EXAM_HPP
#define EXAM_WARE_EXAM_HPP

#include "Question/Question.hpp"
#include "AnswerSheet.hpp"

class ExamAccess;
class ExamMasterAccess;
class ExamStudentAccess;

class Exam
{
    friend class ExamAccess;
    friend class ExamMasterAccess;
    friend class ExamStudentAccess;

public:
    using Id = ::Id;

    Exam();
    Exam(const Exam &) = default;

    Exam &operator=(const Exam &) = default;

    Id getId() const;

    Exam clone() const;

private:
    void addQuestion(Question *);
    void removeQuestion(const Question::Id &);

    Question *getQuestion(const Question::Id &);

    const std::vector<Question *> &getQuestionList() const;

    AnswerSheet startTaking() const;
    void commitAnswerSheet(AnswerSheet);

    Question::Score getMaxScore() const;

    Question *operator[](const Question::Id &);

    int searchQuestion(const Question::Id &) const;

    Id id;

    /*
     * The main answer sheet responsible for questions, their (max) scores and their
     * answers. Here, it is no longer the first element of answerSheets memeber, because
     * this way it is more clear, and also better for making sure it always exists.
     */
    AnswerSheet criteriaSheet;
    std::vector<AnswerSheet> answerSheets;
};

#endif // EXAM_WARE_EXAM_HPP
