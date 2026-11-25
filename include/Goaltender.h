#ifndef GOALTENDER_H
#define GOALTENDER_H

#include <Player.h>

struct GoalStats_t {
    u16 gp = 0;
    u16 mp = 0;
    u16 shot = 0;
    u16 save = 0;
    u8 shutout = 0;
    float svPct = 0.0f;
};

struct GoalCalc_t {
    float gsaa = 0.0f;
    float gsaa60 = 0.0f;
    float adjSvPct = 0.0f;
    float shot60 = 0.0f;
    float minShare = 0.0f;
};

struct GoalPercentiles_t {
    u16 gp = 0;
    u16 mp = 0;
    u16 shot = 0;
    u16 save = 0;
    u8 shutout = 0;
    float svPct = 0.0f;
    float gsaa = 0.0f;
    float gsaa60 = 0.0f;
    float adjSvPct = 0.0f;
    float shot60 = 0.0f;
    float minShare = 0.0f;
};

struct Goaltender_t {
    Info_t info{};
    GoalStats_t stats{};
    GoalCalc_t calc{};
    GoalPercentiles_t percentiles{};
};

namespace Goaltender
{
    void calcStats(Goaltender_t& player);
}

#endif // !GOALTENDER_H
