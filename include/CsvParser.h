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
    ~CsvParser();

    std::vector<std::string> data() const;

    void setInterestColumns(const std::vector<int>& columns);

    void close();
    bool nextLine();

private:
    std::ifstream mFile;
    CsvRow mRow;
};

#endif // !CSV_PARSER_H
