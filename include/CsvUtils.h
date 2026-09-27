#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
#include <unordered_map>

#include "Player.h"

namespace CsvUtils
{
    void load(const char* filePath, char** buffer, size_t& size);

    void interpretTeam(Teams_t& teams, const char* buffer, size_t size);

    void interpretMaster(const Teams_t& teams,
                         Players_t& players,
                         const char* buffer,
                         size_t size);
    void interpretRatings(Players_t& players, const char* buffer, size_t size);
    void interpretStats(Players_t& players, const char* buffer, size_t size);
};

#endif // !CSV_UTILS_H
