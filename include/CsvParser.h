#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <istream>
#include <string>
#include <vector>

#include "CsvRow.h"

class CsvParser {
public:
    CsvParser(std::istream& file);
    ~CsvParser() = default;

    std::vector<std::string> data() const;

    void setInterestColumns(const std::vector<int>& columns);

    bool nextLine();

private:
    std::istream& mFile;
    CsvRow mRow;
};

#endif // !CSV_PARSER_H
