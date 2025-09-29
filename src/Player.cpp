#include "Player.h"

#include <iostream>

bool hasId(std::string id, const std::vector<Player>& players)
{
    int idFormatted = std::stoi(id);
    if (std::find_if(
          players.begin(),
          players.end(),
          [idFormatted](const Player& player) { return player.info.playerId == idFormatted; })
        != players.end()) {
        return true;
    }
    return false;
}

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
    player.stats.gamesPlayed = std::stoi(stats[3]);
}

void PlayerUtils::print(const Player& player)
{
    std::cout << player.info.firstName << ' ' << player.info.lastName << " [" << player.info.playerId
              << "] played " << player.stats.gamesPlayed << " games\n";
}