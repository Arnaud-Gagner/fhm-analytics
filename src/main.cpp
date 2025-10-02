#include "CsvParser.h"
#include "CsvRow.h"
#include "Player.h"

#include <fstream>
#include <iomanip>
#include <iostream>

void printDefHeader()
{
    std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(9)
              << "GP" << std::setw(9) << "Goals" << std::setw(9) << "A" << std::setw(9)
              << "Points" << std::setw(9) << "+/-" << std::setw(9) << "evATOI"
              << std::setw(9) << "ATOI" << std::setw(9) << "Goals/60" << std::setw(9)
              << "evA/60" << std::setw(9) << "A/60" << std::setw(9) << "Shots/60"
              << std::setw(9) << "Shot%" << std::setw(9) << "Hits/60" << std::setw(9)
              << "TK/60" << std::setw(9) << "TK rel" << std::setw(9) << "SBlk/60" << '\n';
}

int main()
{
    std::vector<Player> potentialPlayers = {};
    std::vector<Player> freeAgents = {};

    CsvParser PlayerStatsParser("D:/csv/player_skater_career_stats_rs.csv");
    PlayerStatsParser.nextLine();

    int lastPlayer = -1;
    while (PlayerStatsParser.nextLine() && PlayerStatsParser.data().size() != 0) {
        try {
            const std::vector<std::string>& lineData = PlayerStatsParser.data();
            int currentPlayer = std::stoi(lineData[0]);
            if (lineData[1] == "2021" && lineData[2] == "0") {
            //if (lineData[1] == "2021" && lineData[0] == "23734") {
                if (currentPlayer == lastPlayer) {
                    PlayerUtils::appendStats(potentialPlayers.back(), lineData);
                }
                else {
                    potentialPlayers.push_back(Player());
                    PlayerUtils::setStats(potentialPlayers.back(), lineData);
                }
                lastPlayer = currentPlayer;
            }
        }
        catch (...) {
        }
    }

    CsvParser PlayerPositionsParser("D:/csv/player_ratings.csv");
    PlayerPositionsParser.nextLine();

    while (PlayerPositionsParser.nextLine() && PlayerPositionsParser.data().size() != 0) {
        try {
            int index = PlayerUtils::playerIndex(PlayerPositionsParser.data()[0],
                                                 potentialPlayers);
            if (index != -1) {
                PlayerUtils::setPositions(potentialPlayers[static_cast<size_t>(index)],
                                          PlayerPositionsParser.data());
            }
        }
        catch (...) {
        }
    }

    CsvParser PlayerInfoParser("D:/csv/player_master.csv");
    PlayerInfoParser.nextLine();

    while (PlayerInfoParser.nextLine() && PlayerInfoParser.data().size() != 0) {
        try {
            int index
              = PlayerUtils::playerIndex(PlayerInfoParser.data()[0], potentialPlayers);
            if (index != -1 && PlayerInfoParser.data()[1] == "-1") {
                freeAgents.push_back(
                  std::move(potentialPlayers[static_cast<size_t>(index)]));
                PlayerUtils::setInfo(freeAgents.back(), PlayerInfoParser.data());
                PlayerUtils::setInfo(potentialPlayers[static_cast<size_t>(index)],
                                     PlayerInfoParser.data());
            }
            else if (index != -1) {
                PlayerUtils::setInfo(potentialPlayers[static_cast<size_t>(index)],
                                     PlayerInfoParser.data());
            }
        }
        catch (...) {
        }
    }

    std::vector<Player> filteredPlayer = {};
    for (const Player& player : potentialPlayers) {
        if (player.stats.gamesPlayed > 0) {
            filteredPlayer.push_back(std::move(player));
        }
    }

    printDefHeader();
    for (Player& player : filteredPlayer) {
        if (!player.positions.isLeftDefenseman && !player.positions.isRightDefenseman) {
            PlayerUtils::customStats(player);
            PlayerUtils::printDef(player);
        }
    }
    for (Player& player : filteredPlayer) {
        if (player.positions.isLeftDefenseman || player.positions.isRightDefenseman) {
            PlayerUtils::customStats(player);
            PlayerUtils::printDef(player);
        }
    }
    return 0;
}