#include "Player.h"

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
    std::cout << player.info.firstName << ' ' << player.info.lastName
              << " | ID: " << player.info.playerId << "\n\t" << player.stats.gamesPlayed
              << '-' << player.stats.goals << '-' << player.stats.assists << '\n';
}