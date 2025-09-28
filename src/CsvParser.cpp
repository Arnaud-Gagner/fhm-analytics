#include "CsvParser.h"

#include "CsvRow.h"

CsvParser::CsvParser(const char* filepath)
  : mFile(filepath)
{}

CsvParser::~CsvParser()
{
    if (mFile.is_open()) {
        mFile.close();
    }
}

std::vector<std::string> CsvParser::data() const
{
    return mRow.data();
}

void CsvParser::setInterestColumns(const std::vector<int>& columns)
{
    mRow.setInterestColumns(columns);
}

void CsvParser::close()
{
    if (mFile.is_open()) {
        mFile.close();
    }
}

bool CsvParser::nextLine()
{
    std::string lineContent;
    if (!std::getline(mFile, lineContent)) {
        return false;
    }
    mRow.setRawData(lineContent);

    return true;
}
