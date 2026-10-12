#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <unordered_map>

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
    u8 cf = 0;
    u8 ca = 0;
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
    float atoi = 0;
    float aevtoi = 0;
    float apptoi = 0;
    float ashtoi = 0;
    float goal60 = 0.0f;
    float assist60 = 0.0f;
    float pt60 = 0.0f;
    float evGoal60 = 0.0f;
    float evAssist60 = 0.0f;
    float evPt60 = 0.0f;
    float shot60 = 0.0f;
    float hit60 = 0.0f;
    float sb60 = 0.0f;
    float tkDiff60 = 0.0f;
    float sfDiff60 = 0.0f;
    float gfDiff60 = 0.0f;
};

struct Player_t {
    Info_t info{};
    Position_t position{};
    Stats_t stat{};
    CalcStats_t calc{};
};

namespace Player
{
    void calcStats(Player_t& player);
}

#endif // !PLAYER_H
