#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>

namespace CsvUtils
{
    void load(const char* filePath, char** buffer, size_t* size);
};

#endif // !CSV_UTILS_H
