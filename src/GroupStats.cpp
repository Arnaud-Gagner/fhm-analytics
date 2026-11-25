#include "GroupStats.h"

#include <algorithm>
#include <vector>

namespace
{
    struct PlayerPercentile_t {
        float (*player)(const Player_t&);
        float Percentiles_t::* statPercentile;
        bool lowerIsBetter;
    };

#define PLAYER_PERCENTILE(src, field, inv)                                               \
    { [](const Player_t& p) -> float { return static_cast<float>(p.src); },              \
      &Percentiles_t::field,                                                             \
      inv }

    const PlayerPercentile_t StatPercentiles[] = {
        PLAYER_PERCENTILE(stat.goal, goal, false),
        PLAYER_PERCENTILE(stat.assist, assist, false),
        PLAYER_PERCENTILE(stat.plusMinus, plusMinus, false),
        PLAYER_PERCENTILE(stat.pim, pim, true),
        PLAYER_PERCENTILE(stat.ppg, ppg, false),
        PLAYER_PERCENTILE(stat.ppa, ppa, false),
        PLAYER_PERCENTILE(stat.shg, shg, false),
        PLAYER_PERCENTILE(stat.sha, sha, false),
        PLAYER_PERCENTILE(stat.fight, fight, false),
        PLAYER_PERCENTILE(stat.fightWon, fightWon, false),
        PLAYER_PERCENTILE(stat.hit, hit, false),
        PLAYER_PERCENTILE(stat.gva, gva, true),
        PLAYER_PERCENTILE(stat.tka, tka, false),
        PLAYER_PERCENTILE(stat.sb, sb, false),
        PLAYER_PERCENTILE(stat.shot, shot, false),
        PLAYER_PERCENTILE(stat.pdo, pdo, false),
        PLAYER_PERCENTILE(stat.gf60, gf60, false),
        PLAYER_PERCENTILE(stat.ga60, ga60, true),
        PLAYER_PERCENTILE(stat.sf60, sf60, false),
        PLAYER_PERCENTILE(stat.sa60, sa60, true),
        PLAYER_PERCENTILE(stat.cf, cf, false),
        PLAYER_PERCENTILE(stat.ca, ca, true),
        PLAYER_PERCENTILE(stat.cfPer, cfPer, false),
        PLAYER_PERCENTILE(stat.cfRel, cfRel, false),
        PLAYER_PERCENTILE(stat.gwg, gwg, false),
        PLAYER_PERCENTILE(stat.fo, fo, false),
        PLAYER_PERCENTILE(stat.fow, fow, false),
        PLAYER_PERCENTILE(calc.pt, pt, false),
        PLAYER_PERCENTILE(calc.ppPt, ppPt, false),
        PLAYER_PERCENTILE(calc.shPt, shPt, false),
        PLAYER_PERCENTILE(calc.tkDiff, tkDiff, false),
        PLAYER_PERCENTILE(calc.shotPer, shotPer, false),
        PLAYER_PERCENTILE(calc.evGoal, evGoal, false),
        PLAYER_PERCENTILE(calc.evAssist, evAssist, false),
        PLAYER_PERCENTILE(calc.evPt, evPt, false),
        PLAYER_PERCENTILE(calc.goal60, goal60, false),
        PLAYER_PERCENTILE(calc.assist60, assist60, false),
        PLAYER_PERCENTILE(calc.pt60, pt60, false),
        PLAYER_PERCENTILE(calc.evGoal60, evGoal60, false),
        PLAYER_PERCENTILE(calc.evAssist60, evAssist60, false),
        PLAYER_PERCENTILE(calc.evPt60, evPt60, false),
        PLAYER_PERCENTILE(calc.minor60, minor60, true),
        PLAYER_PERCENTILE(calc.shot60, shot60, false),
        PLAYER_PERCENTILE(calc.hit60, hit60, false),
        PLAYER_PERCENTILE(calc.sb60, sb60, false),
        PLAYER_PERCENTILE(calc.tka60, tka60, false),
        PLAYER_PERCENTILE(calc.gva60, gva60, true),
        PLAYER_PERCENTILE(calc.cf60, cf60, false),
        PLAYER_PERCENTILE(calc.ca60, ca60, true),
        PLAYER_PERCENTILE(calc.tkaDiff60, tkaDiff60, false),
        PLAYER_PERCENTILE(calc.sfDiff60, sfDiff60, false),
        PLAYER_PERCENTILE(calc.cfDiff60, cfDiff60, false),
        PLAYER_PERCENTILE(calc.gfDiff60, gfDiff60, false),
        PLAYER_PERCENTILE(calc.nShot60, nShot60, false),
        PLAYER_PERCENTILE(calc.nSb60, nSb60, false),
        PLAYER_PERCENTILE(calc.nSf60, nSf60, false),
        PLAYER_PERCENTILE(calc.nSa60, nSa60, true),
        PLAYER_PERCENTILE(calc.nGf60, nGf60, false),
        PLAYER_PERCENTILE(calc.nGa60, nGa60, true),
        PLAYER_PERCENTILE(calc.ipp, ipp, false),
    };
#undef PLAYER_PERCENTILE

    struct IndexPercentile_t {
        float (*player)(const Player_t&);
        float Percentiles_t::* indexPercentile;
    };

#define INDEX_PERCENTILE(src, field)                                                     \
    { [](const Player_t& p) -> float { return static_cast<float>(p.src); },              \
      &Percentiles_t::field }

    const IndexPercentile_t IndexPercentiles[] = {
        INDEX_PERCENTILE(index.attack, attackIndex),
        INDEX_PERCENTILE(index.defense, defenseIndex),
    };
#undef INDEX_PERCENTILE
}

void GroupStats::append(PlayerGroup_t& playerGroup, Player_t* player)
{
    playerGroup.players.push_back(player);
}

void GroupStats::append(GoalieGroup_t& goalieGroup, Goaltender_t* goalie)
{
    goalieGroup.goalies.push_back(goalie);
}

void GroupStats::loadPercentiles(PlayerGroup_t& playerGroup)
{
    if (playerGroup.players.size() == 0) {
        return;
    }
    const size_t playerNumber = playerGroup.players.size();

    std::vector<float> values(playerNumber);
    std::vector<float> sorted(playerNumber);

    for (const PlayerPercentile_t& statPercentile : StatPercentiles) {
        for (size_t i = 0; i < playerNumber; ++i) {
            values[i] = statPercentile.player(*playerGroup.players[i]);
        }
        sorted = values;
        std::sort(sorted.begin(), sorted.end());

        for (size_t i = 0; i < playerNumber; ++i) {
            auto low = std::lower_bound(sorted.begin(), sorted.end(), values[i]);
            auto high = std::upper_bound(sorted.begin(), sorted.end(), values[i]);
            const float below = static_cast<float>(low - sorted.begin());
            const float equal = static_cast<float>(high - low);
            float percentile
              = (below + 0.5f * equal) / static_cast<float>(playerNumber) * 100.0f;

            if (statPercentile.lowerIsBetter) {
                percentile = 100.0f - percentile;
            }
            (playerGroup.players[i]->percentile).*(statPercentile.statPercentile)
              = percentile;
        }
    }
}

void GroupStats::loadPercentiles(GoalieGroup_t& goalieGroup) {}

void GroupStats::loadIndexPercentiles(PlayerGroup_t& playerGroup)
{
    if (playerGroup.players.size() == 0) {
        return;
    }
    const size_t playerNumber = playerGroup.players.size();

    std::vector<float> values(playerNumber);
    std::vector<float> sorted(playerNumber);

    for (const IndexPercentile_t& indexPercentile : IndexPercentiles) {
        for (size_t i = 0; i < playerNumber; ++i) {
            values[i] = indexPercentile.player(*playerGroup.players[i]);
        }
        sorted = values;
        std::sort(sorted.begin(), sorted.end());

        for (size_t i = 0; i < playerNumber; ++i) {
            auto low = std::lower_bound(sorted.begin(), sorted.end(), values[i]);
            auto high = std::upper_bound(sorted.begin(), sorted.end(), values[i]);
            const float below = static_cast<float>(low - sorted.begin());
            const float equal = static_cast<float>(high - low);
            float percentile
              = (below + 0.5f * equal) / static_cast<float>(playerNumber) * 100.0f;

            (playerGroup.players[i]->percentile).*(indexPercentile.indexPercentile)
              = percentile;
        }
    }
}
