#ifndef FILTER_CONFIG_H
#define FILTER_CONFIG_H

#include <cstdint>
#include <string>

#include "Player.h"

// [AG] when attribute has [2] => idx 0: min, idx 1: max
struct Filter_t {
    char name[64];
    u8 age[2] = { 0, 100 };
    i32 teamId = -2;
    i16 leagueIds[256] = {};
    Position_t postions{};
    Stats_t baseStats[2] = {};
    CalcStats_t brewStats[2] = {};
    char nationailty[32] = {};
};

struct Filters_t {
    Filter_t* items = nullptr;
    u32 count = 0;
    u32 capacity = 0;
};

namespace FilterConfig
{
    void load();
    void save(const Filter_t& filter);

    void create(const Filter_t& filter);
    void destroy(const Filter_t& filter);
    void modify(Filter_t& filter);
    void use(const char name[64]);

    Filter_t filter(const char name[64]);
    Filter_t activeFilter();
}

#endif // !FILTER_CONFIG_H
