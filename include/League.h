#ifndef LEAGUE_H
#define LEAGUE_H

#include <cstdint>
#include <vector>

typedef int16_t i16;
typedef int32_t i32;

struct League_t {
    i16 id = -2;
    char abbreviation[3];
    std::vector<i32> teamIds = {};
};

namespace League
{
    // TODO
    void leagueStats(League_t& league);
}

#endif // !LEAGUE_H
