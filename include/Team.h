#ifndef TEAM_H
#define TEAM_H

#include <vector>

#include "Goaltender.h"
#include "Player.h"

struct TeamStat_t {
    u8 gp = 0;
    u16 gf = 0;
    u16 ga = 0;
    u16 sf = 0;
    u16 sa = 0;
    float faceoffPct = 0.f;
    u16 sb = 0;
    u16 hit = 0;
    u16 tka = 0;
    u16 gva = 0;
    u16 injuryDay = 0;
    float pimPerGp = 0;
    u16 pp = 0;
    u16 ppg = 0;
    u16 ppga = 0;
    u16 sh = 0;
    u16 shg = 0;
    u16 sha = 0;
};

struct TeamRateStat_t {
    float gfPerGp = 0.f;
    float gaPerGp = 0.f;
    float sfPerGp = 0.f;
    float saPerGp = 0.f;
    float sbPerGp = 0.f;
    float tkaPerGp = 0.f;
    float gvaPerGp = 0.f;
    float ppPerGp = 0.f;
    float ppgPerGp = 0.f;
    float ppaPerGp = 0.f;
    float shPerGp = 0.f;
    float shgPerGp = 0.f;
    float shaPerGp = 0.f;
};

struct CustomTeamStat_t {
    float teamShotPct = 0.f;
    float teamSvPct = 0.f;
};

struct Team_t {
    i32 id = -2;
    char city[32];
    char name[32];
    char abbreviation[3];
    i16 leagueId = -2;
    TeamStat_t stats{};
    TeamRateStat_t rateStats{};
    CustomTeamStat_t customStats{};
    std::vector<Player_t*> players = {};
    std::vector<Goaltender_t*> goalies = {};
};

namespace Team
{}

#endif // TEAM_H
