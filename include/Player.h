#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct PlayerMaster {
    int playerId = -1;
    int teamId = -1;
    int franchiseId = -1;
    std::string firstName = "Average";
    std::string lastName = "Joe";
    std::string nickName = "";
    int height = 0;
    int weight = 0;
    std::string dateBirth = "1900-01-01";
    std::string birthCity = "Tokyo";
    std::string birthState = "TOK";
    std::string nationality = "Japon";
};

struct PlayerPositions {
    bool isGoalie = false;
    bool isLeftDefenseman = false;
    bool isRightDefenseman = false;
    bool isCenter = false;
    bool isRightWinger = false;
    bool isLeftWinger = false;
};

struct PlayerStats {
    int gamesPlayed = 0;
    int goals = 0;
    int assists = 0;
    int penalityMin = 0;
    int plusminus = 0;
    int ppGoals = 0;
    int ppAssists = 0;
    int shGoals = 0;
    int shAssists = 0;
    int gamerating = 0;
    int gameWinningGoals = 0;
    int shots = 0;
    int faceoffTaken = 0;
    int faceoffWon = 0;
    int hit = 0;
    int giveaway = 0;
    int takeaway = 0;
    int shotblock = 0;
    int timeOnIce = 0;
    int ppTimeOnIce = 0;
    int shTimeOnIce = 0;
    int fights = 0;
    int fightsWon = 0;
};

struct CustomStats {
    int evGoal = 0;
    int evAssist = 0;
    int points = 0;
    int evPoints = 0;
    int ppPoints = 0;
    int shPoints = 0;
    int takeawayRel = 0;
    // normalized data
    double goal60 = 0.0;
    double assist60 = 0.0;
    double pt60 = 0.0;
    double evGoal60 = 0.0;
    double evAssist60 = 0.0;
    double evPt60 = 0.0;
    double ppGoal60 = 0.0;
    double ppAssist60 = 0.0;
    double ppPt60 = 0.0;
    double shGoal60 = 0.0;
    double shAssist60 = 0.0;
    double shPt60 = 0.0;
    double shots60 = 0.0;
    double hit60 = 0.0;
    double takeaway60 = 0.0;
    double shotblock60 = 0.0;
};

struct Player {
    PlayerMaster info;
    PlayerPositions positions;
    PlayerStats stats;
    CustomStats customs;
};

namespace PlayerUtils
{
void setInfo(Player& player, const std::vector<std::string>& info);
void setPositions(Player& player, const std::vector<std::string>& positions);
void setStats(Player& player, const std::vector<std::string>& stats);
void appendStats(Player& player, const std::vector<std::string>& stats);

void customStats(Player& player);

int playerIndex(const std::string& id, const std::vector<Player>& players);
void print(const Player& player);
}


#endif // !PLAYER_H
