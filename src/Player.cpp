#include "Player.h"

#include <iostream>

bool hasId(std::string id, const std::vector<Player>& players)
{
    int idFormatted = std::stoi(id);
    if (std::find_if(
          players.begin(),
          players.end(),
          [idFormatted](const Player& player) { return player.id() == idFormatted; })
        != players.end()) {
        return true;
    }
    return false;
}

Player::Player() {}

int Player::id() const
{
    return mInfo.playerId;
}

void Player::setInfo(const std::vector<std::string>& info)
{
    mInfo.playerId = std::stoi(info[0]);
    mInfo.teamId = std::stoi(info[1]);
    mInfo.franchiseId = std::stoi(info[2]);
    mInfo.firstName = info[3];
    mInfo.lastName = info[4];
    // TODO: the rest
}

void Player::setPositions(const std::vector<std::string>& positions)
{
    mPositions.isGoalie = std::stoi(positions[1]) > 14;
    mPositions.isLeftDefenseman = std::stoi(positions[2]) > 14;
    mPositions.isRightDefenseman = std::stoi(positions[3]) > 14;
    mPositions.isLeftWinger = std::stoi(positions[4]) > 14;
    mPositions.isCenter = std::stoi(positions[5]) > 14;
    mPositions.isRightWinger = std::stoi(positions[6]) > 14;
}

void Player::setStats(const std::vector<std::string>& stats)
{
    mStats.gamesPlayed = std::stoi(stats[3]);
}

void Player::print() const
{
    std::cout << mInfo.firstName << ' ' << mInfo.lastName << '[' << mInfo.playerId
              << "] "
                 " played "
              << mStats.gamesPlayed << " games" << '\n'
              << '\t' << "goalie: " << mPositions.isGoalie << '\n'
              << '\t' << "left d: " << mPositions.isLeftDefenseman << '\n'
              << '\t' << "right d: " << mPositions.isRightDefenseman << '\n'
              << '\t' << "center: " << mPositions.isCenter << '\n'
              << '\t' << "left winger: " << mPositions.isLeftWinger << '\n'
              << '\t' << "right winger: " << mPositions.isRightWinger << '\n';
}