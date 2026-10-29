#ifndef FHM_ANALYTICS_H
#define FHM_ANALYTICS_H

#include "Player.h"

namespace FhmAnalytics
{
    void init();
    void loadGameFiles();
    void applyFilter();

    void freeAgents();

    const std::vector<Player_t>& filteredPlayers();
}

#endif // !FHM_ANALYTICS_H
