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
    int heigt = 0;
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
    int timeOnIce = 0;
    int ppTimeOnIce = 0;
    int shTimeOnIce = 0;
    int pdo = 0;
    int gf60 = 0;
    int ga60 = 0;
    int sf60 = 0;
    int sa60 = 0;
    int corsiFor = 0;
    int corsiAgainst = 0;
    int corsiPercentage = 0;
    int corsiRelative = 0;
    int fenwickFor = 0;
    int fenwickAgainst = 0;
    int fenwickPercentage = 0;
    int fenwickRelative = 0;
    int gameWinningGoals = 0;
    int faceoffTaken = 0;
    int faceoffWon = 0;
};

struct CustomStats {
    int takeawayRelative = 0;
};

class Player {
public:
    Player();
    ~Player() = default;

    int id() const;

    void setInfo(const std::vector<std::string>& info);
    void setPositions(const std::vector<std::string>& position);
    void setStats(const std::vector<std::string>& stats);

    void calculateCustomStats();

    bool doesPassFilters() const;
    void print() const;

private:
    PlayerMaster mInfo;
    PlayerPositions mPositions;
    PlayerStats mStats;
    CustomStats mCustomStats;
};

bool hasId(std::string id, const std::vector<Player>& players);

#endif // !PLAYER_H
