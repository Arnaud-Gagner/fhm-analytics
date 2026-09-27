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
}

void Player::calcStats(Player_t& player)
{
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
    player.calc.tkRel
      = static_cast<i16>(player.stat.tka) - static_cast<i16>(player.stat.gva);

    player.calc.totalToi = player.stat.toi + player.stat.pptoi + player.stat.shtoi;
    player.calc.aevtoi = atoi(player.stat.toi, player.stat.gp);
    player.calc.apptoi = atoi(player.stat.pptoi, player.stat.gp);
    player.calc.ashtoi = atoi(player.stat.shtoi, player.stat.gp);
    player.calc.atoi = player.calc.aevtoi + player.calc.apptoi + player.calc.ashtoi;

    if (player.stat.toi > 0) {
        player.calc.goal60 = per60(player.stat.goal, player.calc.totalToi);
        player.calc.assist60 = per60(player.stat.assist, player.calc.totalToi);
        player.calc.pt60 = player.calc.goal60 + player.calc.assist60;

        player.calc.evGoal60 = per60(player.calc.evGoal, player.stat.toi);
        player.calc.evAssist60 = per60(player.calc.evAssist, player.stat.toi);
        player.calc.evPt60 = player.calc.evGoal60 + player.calc.evAssist60;

        player.calc.shot60 = per60(player.stat.shot, player.calc.totalToi);
        player.calc.hit60 = per60(player.stat.hit, player.calc.totalToi);
        player.calc.sb60 = per60(player.stat.sb, player.calc.totalToi);
        player.calc.tkRel60 = per60(player.calc.tkRel, player.calc.totalToi);
    }
}
