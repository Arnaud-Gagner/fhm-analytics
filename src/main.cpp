#include "CsvParser.h"
#include "CsvRow.h"
#include "Player.h"

#include <fstream>
#include <iomanip>
#include <iostream>

/*
    TODO v0.2:
        - create yaml parser
        - read configuration
            add focus league
            add focus position
            add print stats
        - program args for custom input folder and config file
*/

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

            if (lineData[1] == "2021" && lineData[3] == "0") {
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
    std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(9)
              << "GP" << std::setw(9) << "Goals" << std::setw(9) << "Points"
              << std::setw(9) << "+/-" << std::setw(9) << "ATOI" << std::setw(9)
              << "Goals/60" << std::setw(9) << "A/60" << std::setw(9) << "Pts/60"
              << std::setw(9) << "Shots/60" << std::setw(9) << "Shot%" << std::setw(9)
              << "Hits/60" << std::setw(9) << "TK/60" << std::setw(9) << "TK rel"
              << std::setw(9) << "SBlk/60" << '\n';

    for (Player& player : freeAgents) {
        if ((player.positions.isLeftDefenseman || player.positions.isRightDefenseman)
            && player.stats.gamesPlayed >= 20) {
            PlayerUtils::customStats(player);
            // if (player.customs.shots60 > 20.0) {
            PlayerUtils::print(player);
            //}
        }
    }
    return 0;
}