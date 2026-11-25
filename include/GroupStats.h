#ifndef GROUP_STATS_H
#define GROUP_STATS_H

#include <vector>

#include "Goaltender.h"
#include "Player.h"

struct PlayerGroup_t {
    std::vector<Player_t*> players = {};
};

struct GoalieGroup_t {
    std::vector<Goaltender_t*> goalies = {};
};

namespace GroupStats
{
    void append(PlayerGroup_t& playerGroup, Player_t* player);
    void append(GoalieGroup_t& goalieGroup, Goaltender_t* goalie);

    void loadPercentiles(PlayerGroup_t& playerGroup);
    void loadPercentiles(GoalieGroup_t& goalieGroup);
    void loadIndexPercentiles(PlayerGroup_t& groupstats);
}

#endif // !GROUP_STATS_H
