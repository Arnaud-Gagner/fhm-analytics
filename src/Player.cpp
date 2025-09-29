#include "Player.h"

#include <iomanip>
#include <iostream>

void PlayerUtils::setInfo(Player& player, const std::vector<std::string>& info)
{
    player.info.playerId = std::stoi(info[0]);
    player.info.teamId = std::stoi(info[1]);
    player.info.franchiseId = std::stoi(info[2]);
    player.info.firstName = info[3];
    player.info.lastName = info[4];
    player.info.nickName = info[5];
    player.info.height = std::stoi(info[6]);
    player.info.weight = std::stoi(info[7]);
    player.info.dateBirth = info[8];
    player.info.birthCity = info[9];
    player.info.birthState = info[10];
    player.info.nationality = info[11];
}

void PlayerUtils::setPositions(Player& player, const std::vector<std::string>& positions)
{
    player.positions.isGoalie = std::stoi(positions[1]) > 14;
    player.positions.isLeftDefenseman = std::stoi(positions[2]) > 14;
    player.positions.isRightDefenseman = std::stoi(positions[3]) > 14;
    player.positions.isLeftWinger = std::stoi(positions[4]) > 14;
    player.positions.isCenter = std::stoi(positions[5]) > 14;
    player.positions.isRightWinger = std::stoi(positions[6]) > 14;
}

void PlayerUtils::setStats(Player& player, const std::vector<std::string>& stats)
{
    player.info.playerId = std::stoi(stats[0]);
    player.stats.gamesPlayed = std::stoi(stats[4]);
    player.stats.goals = std::stoi(stats[5]);
    player.stats.assists = std::stoi(stats[6]);
    player.stats.penalityMin = std::stoi(stats[7]);
    player.stats.plusminus = std::stoi(stats[8]);
    player.stats.ppGoals = std::stoi(stats[9]);
    player.stats.ppAssists = std::stoi(stats[10]);
    player.stats.shGoals = std::stoi(stats[11]);
    player.stats.shAssists = std::stoi(stats[12]);
    player.stats.gamerating = std::stoi(stats[13]);
    player.stats.gameWinningGoals = std::stoi(stats[14]);
    player.stats.shots = std::stoi(stats[15]);
    player.stats.faceoffTaken = std::stoi(stats[16]);
    player.stats.faceoffWon = std::stoi(stats[17]);
    player.stats.hit = std::stoi(stats[18]);
    player.stats.giveaway = std::stoi(stats[19]);
    player.stats.takeaway = std::stoi(stats[20]);
    player.stats.shotblock = std::stoi(stats[21]);
    player.stats.timeOnIce = std::stoi(stats[22]);
    player.stats.ppTimeOnIce = std::stoi(stats[23]);
    player.stats.shTimeOnIce = std::stoi(stats[24]);
    player.stats.fights = std::stoi(stats[25]);
}

void PlayerUtils::appendStats(Player& player, const std::vector<std::string>& stats)
{
    player.info.playerId += std::stoi(stats[0]);
    player.stats.gamesPlayed += std::stoi(stats[4]);
    player.stats.goals += std::stoi(stats[5]);
    player.stats.assists += std::stoi(stats[6]);
    player.stats.penalityMin += std::stoi(stats[7]);
    player.stats.plusminus += std::stoi(stats[8]);
    player.stats.ppGoals += std::stoi(stats[9]);
    player.stats.ppAssists += std::stoi(stats[10]);
    player.stats.shGoals += std::stoi(stats[11]);
    player.stats.shAssists += std::stoi(stats[12]);
    player.stats.gamerating += std::stoi(stats[13]);
    player.stats.gameWinningGoals += std::stoi(stats[14]);
    player.stats.shots += std::stoi(stats[15]);
    player.stats.faceoffTaken += std::stoi(stats[16]);
    player.stats.faceoffWon += std::stoi(stats[17]);
    player.stats.hit += std::stoi(stats[18]);
    player.stats.giveaway += std::stoi(stats[19]);
    player.stats.takeaway += std::stoi(stats[20]);
    player.stats.shotblock += std::stoi(stats[21]);
    player.stats.timeOnIce += std::stoi(stats[22]);
    player.stats.ppTimeOnIce += std::stoi(stats[23]);
    player.stats.shTimeOnIce += std::stoi(stats[24]);
    player.stats.fights += std::stoi(stats[25]);
}

void PlayerUtils::customStats(Player& player)
{
    player.customs.evGoal
      = player.stats.goals - player.stats.ppGoals - player.stats.shGoals;
    player.customs.evAssist
      = player.stats.assists - player.stats.ppAssists - player.stats.shAssists;
    player.customs.points = player.stats.goals + player.stats.assists;
    player.customs.evPoints = player.customs.evGoal + player.customs.evAssist;
    player.customs.ppPoints = player.stats.ppAssists + player.stats.ppGoals;
    player.customs.shPoints = player.stats.shAssists + player.stats.shGoals;
    player.customs.takeawayRel = player.stats.takeaway - player.stats.giveaway;
    player.customs.shotPercentage = static_cast<double>(player.stats.goals)
                                    / static_cast<double>(player.stats.shots) * 100.0;
    player.customs.atoi = static_cast<double>(player.stats.timeOnIce)
                          / static_cast<double>(player.stats.gamesPlayed) / 60.0;

    if (player.stats.timeOnIce > 0) {
        player.customs.goal60 = static_cast<double>(player.stats.goals)
                                / static_cast<double>(player.stats.timeOnIce)
                                * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.assist60 = static_cast<double>(player.stats.assists)
                                  / static_cast<double>(player.stats.timeOnIce)
                                  * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.pt60 = static_cast<double>(player.customs.points)
                              / static_cast<double>(player.stats.timeOnIce)
                              * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.evGoal60 = static_cast<double>(player.customs.evGoal)
                                  / static_cast<double>(player.stats.timeOnIce)
                                  * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.evAssist60 = static_cast<double>(player.customs.evAssist)
                                    / static_cast<double>(player.stats.timeOnIce)
                                    * static_cast<double>(player.stats.gamesPlayed)
                                    * 60.0;
        player.customs.evPt60 = static_cast<double>(player.customs.evPoints)
                                / static_cast<double>(player.stats.timeOnIce)
                                * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.ppGoal60 = static_cast<double>(player.stats.ppGoals)
                                  / static_cast<double>(player.stats.timeOnIce)
                                  * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.ppAssist60 = static_cast<double>(player.stats.ppAssists)
                                    / static_cast<double>(player.stats.timeOnIce)
                                    * static_cast<double>(player.stats.gamesPlayed)
                                    * 60.0;
        player.customs.ppPt60 = static_cast<double>(player.customs.ppPoints)
                                / static_cast<double>(player.stats.timeOnIce)
                                * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.shGoal60 = static_cast<double>(player.stats.shGoals)
                                  / static_cast<double>(player.stats.timeOnIce)
                                  * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.shAssist60 = static_cast<double>(player.stats.shAssists)
                                    / static_cast<double>(player.stats.timeOnIce)
                                    * static_cast<double>(player.stats.gamesPlayed)
                                    * 60.0;
        player.customs.shPt60 = static_cast<double>(player.customs.shPoints)
                                / static_cast<double>(player.stats.timeOnIce)
                                * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.shots60 = static_cast<double>(player.stats.shots)
                                 / static_cast<double>(player.stats.timeOnIce)
                                 * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.hit60 = static_cast<double>(player.stats.hit)
                               / static_cast<double>(player.stats.timeOnIce)
                               * static_cast<double>(player.stats.gamesPlayed) * 60.0;
        player.customs.takeaway60 = static_cast<double>(player.stats.takeaway)
                                    / static_cast<double>(player.stats.timeOnIce)
                                    * static_cast<double>(player.stats.gamesPlayed)
                                    * 60.0;
        player.customs.shotblock60 = static_cast<double>(player.stats.shotblock)
                                     / static_cast<double>(player.stats.timeOnIce)
                                     * static_cast<double>(player.stats.gamesPlayed)
                                     * 60.0;
    }
}

int PlayerUtils::playerIndex(const std::string& id, const std::vector<Player>& players)
{
    int idFormatted = std::stoi(id);
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].info.playerId == idFormatted) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void PlayerUtils::print(const Player& player)
{
    std::string fullName = player.info.firstName + " " + player.info.lastName;

    std::cout << std::left << std::setw(20) << fullName << std::setw(12)
              << player.stats.gamesPlayed << std::setw(9) << player.stats.goals
              << std::setw(9) << player.customs.points << std::setw(9)
              << player.customs.atoi << std::setw(9) << std::fixed
              << std::setprecision(2) << player.customs.goal60 << std::setw(9)
              << player.customs.assist60 << std::setw(9) << player.customs.pt60
              << std::setw(9) << player.customs.shots60 << std::setw(9)
              << player.customs.shotPercentage << std::setw(9) << player.customs.hit60
              << std::setw(9) << player.customs.takeaway60 << std::setw(9)
              << player.customs.shotblock60 << std::endl;
}