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
    int j = 0;
    while (PlayerPositionsParser.nextLine() && PlayerPositionsParser.data().size() != 0) {
        if (hasId(PlayerPositionsParser.data()[0], potentialPlayers)) {
            PlayerUtils::setPositions(potentialPlayers[j], PlayerPositionsParser.data());
            j++;
        }
    }

    CsvParser PlayerStatsParser("D:/csv/player_skater_stats_rs.csv");

    PlayerStatsParser.nextLine();
    while (PlayerStatsParser.nextLine()) {}
    std::cout << std::clock() - start;
    return 0;
}