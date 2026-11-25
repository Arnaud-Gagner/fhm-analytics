#include "GroupStats.h"

#include <algorithm>
#include <vector>

namespace
{
    struct StatPercentile_t {
        float (*player)(const Player_t&);
        float Percentiles_t::* statPercentile;
        bool lowerIsBetter;
    };

#define STAT_PERCENTILE(src, field, inv)                                                 \
    { [](const Player_t& p) -> float { return static_cast<float>(p.src); },              \
      &Percentiles_t::field,                                                             \
      inv }

    const StatPercentile_t StatPercentiles[] = {
        STAT_PERCENTILE(stat.goal, goal, false),
        STAT_PERCENTILE(stat.assist, assist, false),
        STAT_PERCENTILE(stat.plusMinus, plusMinus, false),
        STAT_PERCENTILE(stat.pim, pim, true),
        STAT_PERCENTILE(stat.ppg, ppg, false),
        STAT_PERCENTILE(stat.ppa, ppa, false),
        STAT_PERCENTILE(stat.shg, shg, false),
        STAT_PERCENTILE(stat.sha, sha, false),
        STAT_PERCENTILE(stat.fight, fight, false),
        STAT_PERCENTILE(stat.fightWon, fightWon, false),
        STAT_PERCENTILE(stat.hit, hit, false),
        STAT_PERCENTILE(stat.gva, gva, true),
        STAT_PERCENTILE(stat.tka, tka, false),
        STAT_PERCENTILE(stat.sb, sb, false),
        STAT_PERCENTILE(stat.shot, shot, false),
        STAT_PERCENTILE(stat.pdo, pdo, false),
        STAT_PERCENTILE(stat.gf60, gf60, false),
        STAT_PERCENTILE(stat.ga60, ga60, true),
        STAT_PERCENTILE(stat.sf60, sf60, false),
        STAT_PERCENTILE(stat.sa60, sa60, true),
        STAT_PERCENTILE(stat.cf, cf, false),
        STAT_PERCENTILE(stat.ca, ca, true),
        STAT_PERCENTILE(stat.cfPer, cfPer, false),
        STAT_PERCENTILE(stat.cfRel, cfRel, false),
        STAT_PERCENTILE(stat.gwg, gwg, false),
        STAT_PERCENTILE(stat.fo, fo, false),
        STAT_PERCENTILE(stat.fow, fow, false),
        STAT_PERCENTILE(calc.pt, pt, false),
        STAT_PERCENTILE(calc.ppPt, ppPt, false),
        STAT_PERCENTILE(calc.shPt, shPt, false),
        STAT_PERCENTILE(calc.tkDiff, tkDiff, false),
        STAT_PERCENTILE(calc.shotPer, shotPer, false),
        STAT_PERCENTILE(calc.evGoal, evGoal, false),
        STAT_PERCENTILE(calc.evAssist, evAssist, false),
        STAT_PERCENTILE(calc.evPt, evPt, false),
        STAT_PERCENTILE(calc.goal60, goal60, false),
        STAT_PERCENTILE(calc.assist60, assist60, false),
        STAT_PERCENTILE(calc.pt60, pt60, false),
        STAT_PERCENTILE(calc.evGoal60, evGoal60, false),
        STAT_PERCENTILE(calc.evAssist60, evAssist60, false),
        STAT_PERCENTILE(calc.evPt60, evPt60, false),
        STAT_PERCENTILE(calc.minor60, minor60, true),
        STAT_PERCENTILE(calc.shot60, shot60, false),
        STAT_PERCENTILE(calc.hit60, hit60, false),
        STAT_PERCENTILE(calc.sb60, sb60, false),
        STAT_PERCENTILE(calc.tka60, tka60, false),
        STAT_PERCENTILE(calc.gva60, gva60, true),
        STAT_PERCENTILE(calc.cf60, cf60, false),
        STAT_PERCENTILE(calc.ca60, ca60, true),
        STAT_PERCENTILE(calc.tkaDiff60, tkaDiff60, false),
        STAT_PERCENTILE(calc.sfDiff60, sfDiff60, false),
        STAT_PERCENTILE(calc.cfDiff60, cfDiff60, false),
        STAT_PERCENTILE(calc.gfDiff60, gfDiff60, false),
        STAT_PERCENTILE(calc.nShot60, nShot60, false),
        STAT_PERCENTILE(calc.nSb60, nSb60, false),
        STAT_PERCENTILE(calc.nSf60, nSf60, false),
        STAT_PERCENTILE(calc.nSa60, nSa60, true),
        STAT_PERCENTILE(calc.nGf60, nGf60, false),
        STAT_PERCENTILE(calc.nGa60, nGa60, true),
        STAT_PERCENTILE(calc.ipp, ipp, false),
    };
#undef STAT_PERCENTILE

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

void GroupStats::append(GroupStats_t& groupStats, Player_t* player)
{
    groupStats.players.push_back(player);
}

void GroupStats::loadPercentiles(GroupStats_t& groupStats)
{
    if (groupStats.players.size() == 0) {
        return;
    }
    const size_t playerNumber = groupStats.players.size();

    std::vector<float> values(playerNumber);
    std::vector<float> sorted(playerNumber);

    for (const StatPercentile_t& statPercentile : StatPercentiles) {
        for (size_t i = 0; i < playerNumber; ++i) {
            values[i] = statPercentile.player(*groupStats.players[i]);
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
            (groupStats.players[i]->percentile).*(statPercentile.statPercentile)
              = percentile;
        }
    }
}

void GroupStats::loadIndexPercentiles(GroupStats_t& groupStats)
{
    if (groupStats.players.size() == 0) {
        return;
    }
    const size_t playerNumber = groupStats.players.size();

    std::vector<float> values(playerNumber);
    std::vector<float> sorted(playerNumber);

    for (const IndexPercentile_t& indexPercentile : IndexPercentiles) {
        for (size_t i = 0; i < playerNumber; ++i) {
            values[i] = indexPercentile.player(*groupStats.players[i]);
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

            (groupStats.players[i]->percentile).*(indexPercentile.indexPercentile)
              = percentile;
        }
    }
}
