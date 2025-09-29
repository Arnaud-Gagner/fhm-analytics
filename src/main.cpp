#include "CsvParser.h"
#include "CsvRow.h"
#include "Player.h"

#include <fstream>
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
    clock_t start = std::clock();
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
        catch (...) {}

    }

    CsvParser PlayerInfoParser("D:/csv/player_master.csv");
    PlayerInfoParser.nextLine();

    while (PlayerInfoParser.nextLine() && PlayerInfoParser.data().size() != 0) {
        try {
            int index = PlayerUtils::playerIndex(PlayerInfoParser.data()[0], potentialPlayers);
            if (index != -1 && PlayerInfoParser.data()[1] == "-1") {
                freeAgents.push_back(std::move(potentialPlayers[static_cast<size_t>(index)]));
                PlayerUtils::setInfo(freeAgents.back(), PlayerInfoParser.data());
            }
            else if (index != -1) {
                PlayerUtils::setInfo(potentialPlayers[static_cast<size_t>(index)], PlayerInfoParser.data());
            }
        }
        catch (...) {
        }
    }
    
    CsvParser PlayerPositionsParser("D:/csv/player_ratings.csv");
    PlayerPositionsParser.nextLine();

    while (PlayerPositionsParser.nextLine() && PlayerPositionsParser.data().size() != 0) {
        try {
            int index = PlayerUtils::playerIndex(PlayerPositionsParser.data()[0], potentialPlayers);
            if (index != -1) {
                PlayerUtils::setPositions(potentialPlayers[static_cast<size_t>(index)], PlayerPositionsParser.data());
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

    for (const Player& player : freeAgents) {
        //if ((float)(player.stats.goals) / (float)(player.stats.timeOnIce)              * player.stats.gamesPlayed * 60            > 1.4) {
            PlayerUtils::print(player);
        //}
    }

    std::cout << std::clock() - start;
    return 0;
}