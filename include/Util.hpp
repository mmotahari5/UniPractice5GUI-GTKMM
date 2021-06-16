#ifndef EXAM_WARE_UTIL_HPP
#define EXAM_WARE_UTIL_HPP

#include <stdexcept>
#include <random>
#include <fstream>

#define NEW_LINE "\n\r"

using Id = std::string;
using IdPrefix = std::string;
using Path = std::string;
using Password = std::string;

bool containsEnglishWords(const std::string &);

Id generateRandomId(const IdPrefix &);

using Name = std::string;

void ensureIsNullptr(const void *, const Name &);
void ensureIsNotNullptr(const void *, const Name &);

using LineVector = std::vector<std::string>;

template<typename FStream>
FStream fileOpen(Path, std::ios_base::openmode = {});

size_t fileSize(Path);
LineVector fileGetLines(Path);
void filePutLines(Path, LineVector);

Path dirname(Path);
Path joinPath(std::vector<Path>);

#endif // EXAM_WARE_UTIL_HPP
