#include "CsvParser.h"

#include "CsvRow.h"

CsvParser::CsvParser(const char* filepath)
    : mFile(filepath)
{
}

CsvParser::~CsvParser()
{
    mFile.close();
}

std::vector<std::string> CsvParser::data() const
{
    return mRow.data();
}

void CsvParser::setInterestColumns(const std::vector<int>& columns)
{
    mRow.setInterestColumns(columns);
}

bool CsvParser::nextLine()
{
    std::string lineContent;
    if (!std::getline(mFile, lineContent)) { return false; }
    mRow.setRawData(lineContent);

    return true;
}
