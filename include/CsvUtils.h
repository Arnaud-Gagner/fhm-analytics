#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
#include <vector>

#include "Player.h"

namespace CsvUtils
{
    void load(const char* filePath, char** buffer, size_t& size);

    void interpretMaster(std::vector<Player_t>& players, const char* buffer, size_t size);
    void interpretRatings(const char* buffer, size_t size);
    void interpretSats(const char* buffer, size_t size);
};

#endif // !CSV_UTILS_H
