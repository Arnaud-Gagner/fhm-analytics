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
    CsvParser PlayerInfoParser("D:/csv/player_master.csv");

    PlayerInfoParser.nextLine();
    while (PlayerInfoParser.nextLine() && PlayerInfoParser.data().size() != 0) {
        const std::vector<std::string>& lineData = PlayerInfoParser.data();
        try {
            int teamID = std::stoi(lineData[1]);
            if (teamID < 36 && teamID >= 0) {
                Player newPlayer = Player();
                PlayerUtils::setInfo(newPlayer, lineData);
                potentialPlayers.push_back(std::move(newPlayer));
            }
        }
        catch (...) {
        }
    }

    CsvParser PlayerPositionsParser("D:/csv/player_ratings.csv");
    PlayerPositionsParser.nextLine();
    int i = 0;
    while (PlayerPositionsParser.nextLine() && PlayerPositionsParser.data().size() != 0) {
        if (hasId(PlayerPositionsParser.data()[0], potentialPlayers)) {
            PlayerUtils::setPositions(potentialPlayers[i], PlayerPositionsParser.data());
            i++;
        }
    }

    CsvParser PlayerStatsParser("D:/csv/player_skater_career_stats_rs.csv");
    int j = 0;
    int lastPlayer = -1;
    PlayerStatsParser.nextLine();
    while (PlayerStatsParser.nextLine() && PlayerStatsParser.data().size() != 0) {
        const std::vector<std::string>& lineData = PlayerStatsParser.data();
        int currentPlayer = std::stoi(lineData[0]);
        if (hasId(lineData[0], potentialPlayers) && lineData[1] == "2021"
            && lineData[3] == "0") {

            while (currentPlayer > potentialPlayers[j].info.playerId) {
                j++;
            }
            if (currentPlayer != lastPlayer) {
                PlayerUtils::setStats(potentialPlayers[j], PlayerStatsParser.data());
                j++;
            }
            lastPlayer = currentPlayer;
        }
    }

    std::vector<Player> filteredPlayer = {};
    for (const Player& player : potentialPlayers) {
        if (player.stats.gamesPlayed > 0) {
            filteredPlayer.push_back(std::move(player));
        }
    }
    for (const Player& player : filteredPlayer) {
        if ((float)(player.stats.goals) / (float)(player.stats.timeOnIce)
              * player.stats.gamesPlayed * 60
            > 1.4) {
            PlayerUtils::print(player);
        }
    }

    std::cout << std::clock() - start;
    return 0;
}