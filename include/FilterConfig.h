#ifndef FILTER_CONFIG_H
#define FILTER_CONFIG_H

#include <cstdint>

#include "Player.h"

using u8 = uint8_t;
using u64 = uint64_t;

struct Filter_t {
    u8 minAge = 0;
    u8 maxAge = 100;
    u32 teamId = 0;
    u64 leagueMask[4]{};
    Position_t postions{};
    Stats_t baseStats{};
    CalcStats_t brewStats{};
    char nationailty[32] = {};
};

namespace FilterConfig
{
    void load();
    Filter_t filter();
}

#endif // !FILTER_CONFIG_H
