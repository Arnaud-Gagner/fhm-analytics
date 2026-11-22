#ifndef GROUP_STATS_H
#define GROUP_STATS_H

#include <vector>

#include "Player.h"

struct GroupStats_t {
    std::vector<Player_t*> players = {};
};

namespace GroupStats
{
    void append(GroupStats_t& league, Player_t* player);
    void loadPercentiles(GroupStats_t& league);
    void loadIndexPercentiles(GroupStats_t& groupstats);
}

#endif // !GROUP_STATS_H
