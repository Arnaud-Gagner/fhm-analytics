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
    int plusminus = 0;
    int penalityMin = 0;
    int ppGoals = 0;
    int ppAssists = 0;
    int shGoals = 0;
    int shAssists = 0;
    int fights = 0;
    int fightsWon = 0;
    int hit = 0;
    int giveaway = 0;
    int takeaway = 0;
    int shotblock = 0;
    int gamerating = 0;
    int offensiveGameRating = 0;
    int defensiveGameRating = 0;
    int shots = 0;
    double timeOnIce = 0;
    double ppTimeOnIce = 0;
    double shTimeOnIce = 0;
    double pdo = 0;
    double gf60 = 0;
    double ga60 = 0;
    double sf60 = 0;
    double sa60 = 0;
    int corsiFor = 0;
    int corsiAgainst = 0;
    double corsiPercentage = 0;
    int corsiRelative = 0;
    int fenwickFor = 0;
    int fenwickAgainst = 0;
    int fenwickPercentage = 0;
    double fenwickRelative = 0;
    int gameWinningGoals = 0;
    int faceoffTaken = 0;
    int faceoffWon = 0;
};

struct CustomStats {
    int takeawayRelative = 0;
};

struct Player {
    PlayerMaster info;
    PlayerPositions positions;
    PlayerStats stats;
    CustomStats customs;
};

namespace PlayerUtils {
    void setInfo(Player& player, const std::vector<std::string>& info);
    void setPositions(Player& player, const std::vector<std::string>& positions);
    void setStats(Player& player, const std::vector<std::string>& stats);

    void print(const Player& player);
}

bool hasId(std::string id, const std::vector<Player>& players);

#endif // !PLAYER_H
