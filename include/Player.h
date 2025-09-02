#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct PlayerMaster {
    int playerId;
    int teamId;
    int franchiseId;
    std::string firstName;
    std::string lastName;
    std::string nickName;
    int heigt;
    int weight;
    std::string dateBirth;
    std::string birthCity;
    std::string birthState;
    std::string nationality;
};

struct PlayerPositions {
    bool isGoalie;
    bool isLeftDefenseman;
    bool isRightDefenseman;
    bool isCenter;
    bool isRightWinger;
    bool isLeftWinger;
};

struct PlayerStats {
    int playerId;
    int teamId;
    int franchiseId;
    int gamesPlayed = 0;
    int goals;
    int assists;
    int plusminus;
    int penalityMin;
    int ppGoals;
    int ppAssists;
    int shGoals;
    int shAssists;
    int fights;
    int fightsWon;
    int hit;
    int giveaway;
    int takeaway;
    int shotblock;
    int gamerating;
    int offensiveGameRating;
    int defensiveGameRating;
    int shots;
    int timeOnIce;
    int ppTimeOnIce;
    int shTimeOnIce;
    int pdo;
    int gf60;
    int ga60;
    int sf60;
    int sa60;
    int corsiFor;
    int corsiAgainst;
    int corsiPercentage;
    int corsiRelative;
    int fenwickFor;
    int fenwickAgainst;
    int fenwickPercentage;
    int fenwickRelative;
    int gameWinningGoals;
    int faceoffTaken;
    int faceoffWon;
};

struct CustomStats {
    int takeawayRelative;
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
