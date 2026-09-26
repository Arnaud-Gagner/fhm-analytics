#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <string>

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
    u16 teamId = 0;
    u16 leagueId = 0;
    char firstName[32] = {};
    char lastName[32] = {};
    char birthDate[32] = {};
};

struct Stats_t {
    u16 gp = 0;
    u16 goals = 0;
    u16 assists = 0;
    u16 plusMinus = 0;
    u16 pim = 0;
    u16 ppg = 0;
    u16 ppa = 0;
    u16 shg = 0;
    u16 sha = 0;
    u16 fight = 0;
    u16 fightWon = 0;
    u16 hits = 0;
    u16 gva = 0;
    u16 tka = 0;
    u16 sb = 0;
    u16 shots = 0;
    u16 toi = 0;
    u16 pptoi = 0;
    u16 shtoi = 0;
    float pdo = 0.0f;
    float gf60 = 0.0f;
    float ga60 = 0.0f;
    float sf60 = 0.0f;
    float sa60 = 0.0f;
    float cf = 0.0f;
    float cfRel = 0.0f;
    u16 gwg = 0;
    u16 fo = 0;
    u16 fow = 0;
};

struct Player_t {
    Info_t info{};
    Position_t position{};
    Stats_t stat{};
};

namespace Player
{}

#endif // !PLAYER_H
