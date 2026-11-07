#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

using i16 = int16_t;
using i32 = int32_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

struct Position_t {
    u8 g = 0;
    u8 ld = 0;
    u8 rd = 0;
    u8 lw = 0;
    u8 c = 0;
    u8 rw = 0;
};

struct Info_t {
    u32 id = 0;
    i32 teamId = 0;
    i16 leagueId = 0;
    char firstName[32] = {};
    char lastName[32] = {};
    char birthDate[32] = {};
    char nationality[32] = {};
    char secondNationality[32] = {};
};

struct Stats_t {
    u16 gp = 0;
    u16 goal = 0;
    u16 assist = 0;
    i16 plusMinus = 0;
    u16 pim = 0;
    u16 ppg = 0;
    u16 ppa = 0;
    u16 shg = 0;
    u16 sha = 0;
    u16 fight = 0;
    u16 fightWon = 0;
    u16 hit = 0;
    u16 gva = 0;
    u16 tka = 0;
    u16 sb = 0;
    u16 shot = 0;
    u32 toi = 0;
    u32 pptoi = 0;
    u32 shtoi = 0;
    float pdo = 0.0f;
    float gf60 = 0.0f;
    float ga60 = 0.0f;
    float sf60 = 0.0f;
    float sa60 = 0.0f;
    u16 cf = 0;
    u16 ca = 0;
    float cfPer = 0.0f;
    float cfRel = 0.0f;
    u16 gwg = 0;
    u16 fo = 0;
    u16 fow = 0;
};

struct CalcStats_t {
    u16 pt = 0;
    u16 ppPt = 0;
    u16 shPt = 0;
    i16 tkDiff = 0;
    float shotPer = 0.0f;
    u16 evGoal = 0;
    u16 evAssist = 0;
    u16 evPt = 0;
    u32 totalToi = 0;
    float atoi = 0.0f;
    float aevtoi = 0.0f;
    float apptoi = 0.0f;
    float ashtoi = 0.0f;
    float ppPct = 0.0f;
    float shPct = 0.0f;
    float goal60 = 0.0f;
    float assist60 = 0.0f;
    float pt60 = 0.0f;
    float evGoal60 = 0.0f;
    float evAssist60 = 0.0f;
    float evPt60 = 0.0f;
    float shot60 = 0.0f;
    float hit60 = 0.0f;
    float sb60 = 0.0f;
    float tka60 = 0.0f;
    float gva60 = 0.0f;
    float cf60 = 0.0f;
    float ca60 = 0.0f;
    float tkaDiff60 = 0.0f;
    float sfDiff60 = 0.0f;
    float cfDiff60 = 0.0f;
    float gfDiff60 = 0.0f;
    float minor60 = 0.0f;
    float nShot60 = 0.0f;
    float nSf60 = 0.0f;
    float nSa60 = 0.0f;
    float nGf60 = 0.0f;
    float nGa60 = 0.0f;
    float ipp = 0.0f;
};

struct Percentiles_t {
    float goal = 0.0f;
    float assist = 0.0f;
    float plusMinus = 0.0f;
    float pim = 0.0f;
    float ppg = 0.0f;
    float ppa = 0.0f;
    float shg = 0.0f;
    float sha = 0.0f;
    float fight = 0.0f;
    float fightWon = 0.0f;
    float hit = 0.0f;
    float gva = 0.0f;
    float tka = 0.0f;
    float sb = 0.0f;
    float shot = 0.0f;
    float pdo = 0.0f;
    float gf60 = 0.0f;
    float ga60 = 0.0f;
    float sf60 = 0.0f;
    float sa60 = 0.0f;
    float cf = 0.0f;
    float ca = 0.0f;
    float cfPer = 0.0f;
    float cfRel = 0.0f;
    float gwg = 0.0f;
    float fo = 0.0f;
    float fow = 0.0f;
    float pt = 0.0f;
    float ppPt = 0.0f;
    float shPt = 0.0f;
    float tkDiff = 0.0f;
    float shotPer = 0.0f;
    float evGoal = 0.0f;
    float evAssist = 0.0f;
    float evPt = 0.0f;
    float goal60 = 0.0f;
    float assist60 = 0.0f;
    float pt60 = 0.0f;
    float evGoal60 = 0.0f;
    float evAssist60 = 0.0f;
    float evPt60 = 0.0f;
    float shot60 = 0.0f;
    float minor60 = 0.0f;
    float hit60 = 0.0f;
    float sb60 = 0.0f;
    float tka60 = 0.0f;
    float gva60 = 0.0f;
    float cf60 = 0.0f;
    float ca60 = 0.0f;
    float tkaDiff60 = 0.0f;
    float sfDiff60 = 0.0f;
    float cfDiff60 = 0.0f;
    float gfDiff60 = 0.0f;
    float nShot60 = 0.0f;
    float nSf60 = 0.0f;
    float nSa60 = 0.0f;
    float nGf60 = 0.0f;
    float nGa60 = 0.0f;
    float ipp = 0.0f;
    float attackIndex = 0.0f;
    float defenseIndex = 0.0f;
};

struct Index_t {
    float attack = 0.0f;
    float defense = 0.0f;
};

struct Player_t {
    Info_t info{};
    Position_t position{};
    Stats_t stat{};
    CalcStats_t calc{};
    Percentiles_t percentile{};
    Index_t index{};
};

namespace Player
{
    void calcStats(Player_t& player);
    void indexes(Player_t* player);
}

#endif // !PLAYER_H
