#include "CsvParser.h"

#include <iostream>

#include "CsvRow.h"

CsvParser::CsvParser(const char* filepath)
  : mStartIndex{}
  , mLastIndex{}
{
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0);
    mFileText = std::string(size, '\0');
    file.read(&mFileText[0], size);
    file.close();
}

std::vector<std::string> CsvParser::data() const
{
    return mRow.data();
}

bool CsvParser::nextLine()
{
    mLastIndex = mFileText.find_first_of('\n', mStartIndex);
    std::string lineContent = mFileText.substr(mStartIndex, mLastIndex - mStartIndex);

    mRow.setRawData(lineContent);
    mStartIndex = mLastIndex + 1;

    return mLastIndex != std::string::npos;
}
