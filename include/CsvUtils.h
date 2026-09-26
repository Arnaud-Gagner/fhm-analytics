#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
#include <unordered_map>

#include "Player.h"

namespace CsvUtils
{
    void load(const char* filePath, char** buffer, size_t& size);

    void interpretMaster(std::unordered_map<u32, Player_t>& players,
                         const char* buffer,
                         size_t size);
    void interpretRatings(std::unordered_map<u32, Player_t>& players,
                          const char* buffer,
                          size_t size);
    void interpretStats(std::unordered_map<u32, Player_t>& players,
                        const char* buffer,
                        size_t size);
};

#endif // !CSV_UTILS_H
