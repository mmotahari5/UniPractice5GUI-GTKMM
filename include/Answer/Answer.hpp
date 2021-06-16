#ifndef EXAM_WARE_ANSWER_HPP
#define EXAM_WARE_ANSWER_HPP

class Answer
{
public:
    virtual void clear() = 0;
    virtual operator bool() const = 0;
};

#endif // EXAM_WARE_ANSWER_HPP
