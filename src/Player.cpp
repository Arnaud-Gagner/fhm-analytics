#include "Player.h"

namespace
{
    float atoi(u32 time, u16 gp)
    {
        return static_cast<float>(time) / static_cast<float>(gp);
    }

    float per60(u16 stat, u32 toi)
    {
        return static_cast<float>(stat) / static_cast<float>(toi) * 3600.0f;
    }

    float per60(i16 stat, u32 toi)
    {
        return static_cast<float>(stat) / static_cast<float>(toi) * 3600.0f;
    }

    float per60(float stat, u32 toi)
    {
        return stat / static_cast<float>(toi) * 3600.0f;
    }

    float normalized(float stat, float ppPct, float shPct)
    {
        return stat * (1 - ppPct + shPct);
    }

    float normalizedInv(float stat, float ppPct, float shPct)
    {
        return stat * (1 + ppPct - shPct);
    }
}

void Player::calcStats(Player_t& player)
{
    if (player.stat.toi <= 0) {
        return;
    }

    player.calc.evGoal = player.stat.goal - player.stat.ppg - player.stat.shg;
    player.calc.evAssist = player.stat.assist - player.stat.ppa - player.stat.sha;

    player.calc.pt = player.stat.goal + player.stat.assist;
    player.calc.evPt = player.calc.evGoal + player.calc.evAssist;
    player.calc.ppPt = player.stat.ppg + player.stat.ppa;
    player.calc.shPt = player.stat.shg + player.stat.sha;

    if (player.stat.shot > 0) {
        player.calc.shotPer = static_cast<float>(player.stat.goal)
                              / static_cast<float>(player.stat.shot) * 100.0f;
    }
    player.calc.tkDiff
      = static_cast<i16>(player.stat.tka) - static_cast<i16>(player.stat.gva);

    player.calc.totalToi = player.stat.toi + player.stat.pptoi + player.stat.shtoi;
    player.calc.aevtoi = atoi(player.stat.toi, player.stat.gp);
    player.calc.apptoi = atoi(player.stat.pptoi, player.stat.gp);
    player.calc.ashtoi = atoi(player.stat.shtoi, player.stat.gp);
    player.calc.atoi = player.calc.aevtoi + player.calc.apptoi + player.calc.ashtoi;

    player.calc.ppPct = player.calc.apptoi / (player.calc.atoi);
    player.calc.shPct = player.calc.ashtoi / (player.calc.atoi);

    player.calc.goal60 = per60(player.stat.goal, player.calc.totalToi);
    player.calc.assist60 = per60(player.stat.assist, player.calc.totalToi);
    player.calc.pt60 = player.calc.goal60 + player.calc.assist60;

    player.calc.evGoal60 = per60(player.calc.evGoal, player.stat.toi);
    player.calc.evAssist60 = per60(player.calc.evAssist, player.stat.toi);
    player.calc.evPt60 = player.calc.evGoal60 + player.calc.evAssist60;

    player.calc.minor60
      = per60((u16)(player.stat.pim - 5 * player.stat.fight), player.calc.totalToi);
    player.calc.shot60 = per60(player.stat.shot, player.calc.totalToi);
    player.calc.hit60 = per60(player.stat.hit, player.calc.totalToi);
    player.calc.sb60 = per60(player.stat.sb, player.calc.totalToi);
    player.calc.tka60 = per60(player.stat.tka, player.calc.totalToi);
    player.calc.gva60 = per60(player.stat.gva, player.calc.totalToi);
    player.calc.cf60 = per60(player.stat.cf, player.calc.totalToi);
    player.calc.ca60 = per60(player.stat.ca, player.calc.totalToi);

    player.calc.tkaDiff60 = per60(player.calc.tkDiff, player.calc.totalToi);
    player.calc.sfDiff60
      = per60(player.stat.sf60 - player.stat.sa60, player.calc.totalToi);
    player.calc.cfDiff60
      = per60(player.calc.cf60 - player.calc.ca60, player.calc.totalToi);
    player.calc.gfDiff60
      = per60(player.stat.gf60 - player.stat.ga60, player.calc.totalToi);

    player.calc.nShot60
      = normalized(player.calc.shot60, player.calc.ppPct, player.calc.shPct);
    player.calc.nSf60
      = normalized(player.stat.sf60, player.calc.ppPct, player.calc.shPct);
    player.calc.nSa60
      = normalizedInv(player.stat.sa60, player.calc.ppPct, player.calc.shPct);
    player.calc.nGf60
      = normalized(player.stat.gf60, player.calc.ppPct, player.calc.shPct);
    player.calc.nGa60
      = normalizedInv(player.stat.ga60, player.calc.ppPct, player.calc.shPct);

    float gf = player.stat.gf60 / 3600 * static_cast<float>(player.stat.toi);
    if (gf <= 0.0f) {
        return;
    }
    player.calc.ipp
      = static_cast<float>(player.calc.pt) / static_cast<float>(player.calc.pt + gf);
}

void Player::indexes(Player_t* player)
{
    const Percentiles_t& pct = player->percentile;
    player->index.defense
      = (pct.nSa60 + pct.nGa60 + pct.sb60 + pct.tkaDiff60 + pct.minor60) / 500.0f;
    player->index.attack = (pct.nSf60 + pct.nGf60 + pct.pt60 + pct.nShot60) / 400.0f;
}
