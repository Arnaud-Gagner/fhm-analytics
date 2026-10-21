#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
#include <unordered_map>

#include "Player.h"

namespace CsvUtils
{
    void load(const char* filePath, char** buffer, size_t& size);

    void interpretTeam(std::unordered_map<i32, i16>& teams,
                       const char* buffer,
                       size_t size);

    void interpretMaster(const std::unordered_map<i32, i16>& teams,
                         std::unordered_map<u32, Player_t>& players,
                         const char* buffer,
                         size_t size);
    void interpretRatings(std::unordered_map<u32, Player_t>& players,
                          const char* buffer,
                          size_t size);
    void interpretStats(std::unordered_map<u32, Player_t>& players,
                        const char* buffer,
                        size_t size);
    void updatePlayerTeam(std::unordered_map<u32, Player_t>& players,
                          const char* buffer,
                          size_t size);
};

#endif // !CSV_UTILS_H
