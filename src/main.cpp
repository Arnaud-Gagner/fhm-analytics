#include "CsvParser.h"
#include "CsvRow.h"
#include "Player.h"

#include <fstream>
#include <iomanip>
#include <iostream>

std::string path
  = "C:/Users/INSERT_USER/Documents/Out of the Park Developments/Franchise "
    "Hockey Manager 8/saved_games/canes-rebuild.lg/import_export/csv/";

void printDefHeader()
{
    std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(9)
              << "GP" << std::setw(9) << "Goals" << std::setw(9) << "A" << std::setw(9)
              << "Points" << std::setw(9) << "+/-" << std::setw(9) << "evATOI"
              << std::setw(9) << "ATOI" << std::setw(9) << "Goals/60" << std::setw(9)
              << "evA/60" << std::setw(9) << "A/60" << std::setw(9) << "evPt/60"
              << std::setw(9) << "Shots/60" << std::setw(9) << "Shot%" << std::setw(9)
              << "Hits/60" << std::setw(9) << "TK/60" << std::setw(9) << "TKrel/60"
              << std::setw(9) << "SBlk/60" << '\n';
}

void printOffForwards(std::vector<Player>& players)
{
    for (Player& player : players) {
        PlayerUtils::customStats(player);
        bool isForward = player.positions.isCenter || player.positions.isLeftWinger
                         || player.positions.isRightWinger;
        bool isGoodForward
          = isForward && player.customs.shots60 > 7.0 && player.customs.evPt60 > 2.0;
        if (isGoodForward) {
            PlayerUtils::printDef(player);
        }
    }
}

void printDefForwards(std::vector<Player>& players)
{
    for (Player& player : players) {
        PlayerUtils::customStats(player);
        bool isForward
          = !player.positions.isLeftDefenseman && !player.positions.isRightDefenseman;
        bool isGoodForward = isForward && player.customs.takeawayRel60 > 0.0
                             && player.customs.shotblock60 > 1.0;
        if (isGoodForward) {
            PlayerUtils::printDef(player);
        }
    }
}

void printDefencemen(std::vector<Player>& players)
{
    for (Player& player : players) {
        if (player.positions.isLeftDefenseman || player.positions.isRightDefenseman) {
            PlayerUtils::customStats(player);
            if (player.customs.takeawayRel60 > 0.0 && player.customs.shots60 > 4.0) {
                PlayerUtils::printDef(player);
            }
        }
    }
}

void printEveryone(std::vector<Player>& players)
{
    for (Player& player : players) {
        if (!player.positions.isLeftDefenseman && !player.positions.isRightDefenseman) {
            PlayerUtils::customStats(player);
            PlayerUtils::printDef(player);
        }
    }
    for (Player& player : players) {
        if (player.positions.isLeftDefenseman || player.positions.isRightDefenseman) {
            PlayerUtils::customStats(player);
            PlayerUtils::printDef(player);
        }
    }
}

int main()
{
    std::vector<Player> potentialPlayers = {};
    std::vector<Player> freeAgents = {};

    const std::string statsFileName = path + "player_skater_career_stats_rs.csv";
    CsvParser PlayerStatsParser(statsFileName.c_str());
    PlayerStatsParser.nextLine();

    int lastPlayer = -1;
    while (PlayerStatsParser.nextLine() && PlayerStatsParser.data().size() != 0) {
        try {
            const std::vector<std::string>& lineData = PlayerStatsParser.data();
            int currentPlayer = std::stoi(lineData[0]);
            // 35 -> minnesota && 24 -> carolina
            if (lineData[1] == "2024" && lineData[3] == "0") {
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

    const std::string positionFileName = path + "player_ratings.csv";
    CsvParser PlayerPositionsParser(positionFileName.c_str());
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

    const std::string infoFileName = path + "player_master.csv";
    CsvParser PlayerInfoParser(infoFileName.c_str());
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
        if (player.stats.gamesPlayed >= 10) {
            filteredPlayer.push_back(std::move(player));
        }
    }

    printDefHeader();
    printEveryone(filteredPlayer);
    // printOffForwards(filteredPlayer);
    // std::cout << '\n';
    // printDefHeader();
    // printDefForwards(filteredPlayer);

    // std::cout << '\n';
    // printDefHeader();
    // printDefencemen(filteredPlayer);

    return 0;
}