#ifndef FHM_ANALYTICS_H
#define FHM_ANALYTICS_H

#include <functional>
#include <vector>

#include "Player.h"

namespace FhmAnalytics
{
    void init();

    void loadGameFiles();
    void loadTeams(bool isFA);

    void applyFilter();

    const std::vector<Player_t>& filteredPlayers();

    void setCallBack(const std::function<void(const std::vector<Player_t>&)>& callback);
}

#endif // !FHM_ANALYTICS_H
