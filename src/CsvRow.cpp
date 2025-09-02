#include "CsvRow.h"

CsvRow::CsvRow() {}

std::vector<std::string> CsvRow::data() const
{
    return mInterestData;
}

void CsvRow::setInterestColumns(const std::vector<int>& columns)
{
    mInterestColumns = columns;
}

void CsvRow::setRawData(const std::string& data)
{
    mInterestData = mInternalData = {};
    bool isNextNewElem = false;
    std::string currentElem = "";

    for (int i = 0; i < static_cast<int>(data.size()); i++) {
        if (data[i] == ';') {
            mInternalData.push_back(currentElem);
            isNextNewElem = true;
            currentElem = "";
        }
        else {
            isNextNewElem = false;
            currentElem += data[i];
        }
    }
    // TODO: create function to check in branch of for-loop for interest columns
    //          and check if other solution is quicker
    if (mInterestColumns.size() == 0) {
        mInterestData = mInternalData;
        return;
    }
    int nextInterest = mInterestColumns[0];
    for (int i = 0; i < mInternalData.size(); i++) {
        if (i == nextInterest && nextInterest < mInterestColumns.size()) {
            mInterestData.push_back(mInternalData[i]);
        }
    }
}