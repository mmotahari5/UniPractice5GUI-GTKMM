#include "Course.hpp"

#include "Exam/ExamMasterAccess.hpp"
#include "Exam/ExamStudentAccess.hpp"
#include "Util.hpp"
#include "Exception.hpp"

Course::Course(Name name, Master::Username masterUsername):
    masterUsername(masterUsername)
{
    this->setName(name);
}

void Course::setName(Name name)
{
    if (!containsEnglishWords(name)) {
        throw std::invalid_argument{"Course name must only include english words"};
    }

    this->name = name;
}

Course::Name Course::getName() const
{
    return this->name;
}

void Course::addExam(const LoginManager &loginManager, Exam exam)
{
    this->assertIsRegisteredMaster(loginManager);

    if (this->searchExam(exam.getId()) != -1) {
        throw std::invalid_argument{"An Exam with the same Id already exists"};
    }

    this->exams.push_back(exam); // adding exam
}

void Course::removeExam(const LoginManager &loginManager, const Exam::Id &examId)
{
    this->assertIsRegisteredMaster(loginManager);

    int examIndex = this->searchExam(examId);

    if (examIndex == -1) {
        throw std::invalid_argument{"Exam with the given Id not found"};
    }

    exams.erase(exams.begin() + examIndex);
}

ExamAccess *Course::getExam(const LoginManager &loginManager, const Exam::Id &examId)
{
    int examIndex = this->searchExam(examId);

    if (examIndex == -1) {
        throw std::invalid_argument{"Exam with the given Id not found"};
    }

    if (this->isRegisteredMaster(loginManager)) {
        this->examAccesses.push_back(
            new ExamMasterAccess(this->exams[examIndex])
        );
    } else if (this->isRegisteredStudent(loginManager)) {
        this->examAccesses.push_back(
            new ExamStudentAccess(this->exams[examIndex])
        );
    } else {
        throw AccessDeniedException{};
    }

    // Return the most-recently created object, created above in the ifs
    return this->examAccesses.back();
}

const std::vector<Exam> &Course::getExamList(const LoginManager &loginManager) const
{
    this->assertIsRegisteredMasterOrStudent(loginManager);

    return this->exams;
}

void Course::changeMaster(
    const LoginManager &loginManager,
    Master::Username &newMasterUsername
) {
    this->assertIsRegisteredMaster(loginManager);

    this->masterUsername.swap(newMasterUsername);
}

void Course::registerStudent(
    const LoginManager &loginManager,
    const Student::Username &newStudentUsername
) {
    this->assertIsRegisteredMaster(loginManager);

    if (!this->isStudentRegistered(loginManager, newStudentUsername)) {
        this->studentUsernames.push_back(newStudentUsername);
    } else {
        throw std::invalid_argument{"Student with the given username already registered"};
    }
}

void Course::removeStudent(
    const LoginManager &loginManager,
    const Student::Username &studentUsername
) {
    this->assertIsRegisteredMaster(loginManager);

    size_t studentIndex = this->searchStudent(studentUsername);

    if (studentIndex == -1) {
        throw std::invalid_argument{"Student with such a username not found"};
    }

    this->studentUsernames.erase(this->studentUsernames.begin() + studentIndex);
}

bool Course::isStudentRegistered(
    const LoginManager &loginManager,
    const Student::Username &studentUsername
) const {
    this->assertIsRegisteredMasterOrStudent(loginManager);

    return this->searchStudent(studentUsername) != -1;
}

Course::~Course()
{
    for (ExamAccess *&e: this->examAccesses) {
        delete e;
        e = nullptr;
    }
}

int Course::searchExam(const Exam::Id &examId) const
{
    for (size_t i = 0; i < this->exams.size(); i++) {
        if (examId == this->exams[i].getId()) {
            return i;
        }
    }

    // Id not found
    return -1;
}

int Course::searchStudent(const Student::Username &studentUsername) const
{
    for (size_t i = 0; i < this->studentUsernames.size(); i++) {
        if (studentUsername == this->studentUsernames[i]) {
            return i;
        }
    }

    // Not found
    return -1;
}


bool Course::isRegisteredMaster(const LoginManager &loginManager) const
{
    return loginManager.getCurrentUser()->getUsername() == this->masterUsername;
}

bool Course::isRegisteredStudent(const LoginManager &loginManager) const
{
    const Student::Username &currentStudentUsername =
        loginManager.getCurrentUser()->getUsername();

    for (const Student::Username &username: this->studentUsernames) {
        if (username == currentStudentUsername) {
            return true;
        }
    }

    return false;
}

void Course::assertIsRegisteredMaster(const LoginManager &loginManager) const
{
    if (!this->isRegisteredMaster(loginManager)) {
        throw AccessDeniedException{};
    }
}

void Course::assertIsRegisteredMasterOrStudent(const LoginManager &loginManager) const
{
    if (!(
        this->isRegisteredMaster(loginManager) ||
        this->isRegisteredStudent(loginManager)
    )) {
        throw AccessDeniedException{};
    }
}
