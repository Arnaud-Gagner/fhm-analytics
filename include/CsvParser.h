#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "CsvRow.h"

class CsvParser
{
public:
    CsvParser(const char* filepath);
    ~CsvParser() = default;

    std::vector<std::string> data() const;

    bool nextLine();

private:
    std::string mFileText;
    size_t mLastIndex;
    size_t mStartIndex;

    CsvRow mRow;
};

#endif // !CSV_PARSER_H
