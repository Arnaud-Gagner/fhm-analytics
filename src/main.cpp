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
    std::vector<Player> potentialPlayers = {};

    CsvParser PlayerInfoParser("D:/csv/player_master.csv");
    while (PlayerInfoParser.nextLine()) {
        if (PlayerInfoParser.data().size() != 0 && PlayerInfoParser.data()[1] == "0") {
            Player newPlayer = Player();
            newPlayer.setInfo(PlayerInfoParser.data());
            potentialPlayers.push_back(newPlayer);
        }
    }

    CsvParser PlayerPositionsParser("D:/csv/player_ratings.csv");
    int j = 0;
    PlayerPositionsParser.nextLine();
    while (PlayerPositionsParser.nextLine()) {
        if (PlayerPositionsParser.data().size() != 0
            && j < PlayerPositionsParser.data().size() - 1
            && hasId(PlayerPositionsParser.data()[0], potentialPlayers)) {
            potentialPlayers[j].setPositions(PlayerPositionsParser.data());
            j++;
        }
    }

    CsvParser PlayerStatsParser("D:/csv/player_skater_stats_rs.csv");
    int i = 0;
    PlayerStatsParser.nextLine();
    while (PlayerStatsParser.nextLine()) {
        if (PlayerStatsParser.data().size() != 0
            && i < PlayerStatsParser.data().size() - 1
            && hasId(PlayerStatsParser.data()[0], potentialPlayers)) {

            while (potentialPlayers[i].id() != std::stoi(PlayerStatsParser.data()[0])) {
                i++;
            }
            potentialPlayers[i].setStats(PlayerStatsParser.data());
            potentialPlayers[i].print();
            i++;
        }
    }
    return 0;
}