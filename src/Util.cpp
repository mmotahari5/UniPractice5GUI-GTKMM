#include "Util.hpp"

#include "Exception.hpp"
#include <string>
#include <fstream>
#include <sstream>

#define RANDOM_ID_GENERATOR_LENGTH 10

bool containsEnglishWords(const std::string &str)
{
    for (const char &c : str) {
        if (!(isalnum(c) || c == ' ')) {
            return false;
        }
    }
    return true;
}

Id generateRandomId(const IdPrefix &prefix)
{
    // Create engine only one time
    static std::default_random_engine randEng{
        static_cast<unsigned long>(time(nullptr))
    };
    static std::vector<char> possibleCharacters = {};

    // It is executed only at initial invocation
    if (possibleCharacters.empty()) {
        for (char i = 'a'; i <= 'z'; i++) {
            possibleCharacters.push_back(i);
        }
        for (char i = '0'; i <= '9'; i++) {
            possibleCharacters.push_back(i);
        }
    }

    Id id = prefix + "_";

    std::uniform_int_distribution<size_t> randDist(0, possibleCharacters.size() - 1);

    for (size_t i = 0; i < RANDOM_ID_GENERATOR_LENGTH; i++) {
        id.push_back(possibleCharacters[randDist(randEng)]);
    }

    return id;
}

void ensureIsNullptr(const void *ptr, const Name &ptrName)
{
    if (ptr != nullptr) {
        throw std::invalid_argument(ptrName + " pointer must be a null pointer");
    }
}

void ensureIsNotNullptr(const void *ptr, const Name &ptrName)
{
    if (ptr == nullptr) {
        throw std::invalid_argument(ptrName + " pointer must not be a null pointer");
    }
}

template<typename FStream>
FStream fileOpen(Path path, std::ios_base::openmode mode)
{
    FStream file{path, mode};

    if (!file.is_open()) {
        throw FileOpeningException{};
    }

    return file;
}

template std::ifstream fileOpen(Path, std::ios_base::openmode);
template std::ofstream fileOpen(Path, std::ios_base::openmode);

size_t fileSize(Path path)
{
    return fileOpen<std::ifstream>(path, std::ios_base::ate).tellg();
}

LineVector fileGetLines(Path path)
{
    std::ifstream file = fileOpen<std::ifstream>(path);
    LineVector result;
    std::string line;

    while (!file.eof()) {
        std::getline(file, line);
        result.push_back(line);
    }

    return result;
}

void filePutLines(Path path, LineVector lines)
{
    std::ofstream file = fileOpen<std::ofstream>(path, std::ios_base::trunc);

    auto lineIt = lines.begin();
    for (; lineIt != lines.end() - 1; lineIt++) {
        file << *lineIt << std::endl;
    }

    // Don't put a new line for the last line
    file << *lineIt;
}

Path dirname(Path path)
{
    while (path.back() == '/') {
        path.pop_back();
    }

    if (path.find('/') == Path::npos) {
        throw std::invalid_argument{"Invalid path with no slashes"};
    }

    return path.substr(0, path.find_last_of('/') + 1);
}
