#ifndef CSV_ROW_H
#define CSV_ROW_H

#include <string>
#include <vector>

class CsvRow
{
public:
    CsvRow();
    ~CsvRow() = default;

    std::vector<std::string> data() const;

    void setInterestColumns(const std::vector<int>& columns);
    void setRawData(const std::string& rawData);

private:
    std::vector<std::string> mInternalData = {};
    std::vector<std::string> mInterestData = {};
    std::vector<int> mInterestColumns = {};
};

#endif // !CSV_ROW_H
