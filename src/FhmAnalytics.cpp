#include "FhmAnalytics.h"

#include <mutex>

#include "AppConfig.h"
#include "CsvUtils.h"
#include "FilterConfig.h"
#include "Player.h"

namespace
{
    std::unordered_map<u32, Player_t> UnfilteredPlayers{};
    std::mutex UnfilteredMutex;
}

void FhmAnalytics::init()
{
    AppConfig::load();
    FilterConfig::load();
    loadGameFiles();
}

void FhmAnalytics::loadGameFiles()
{
    std::unique_lock<std::mutex> lock(UnfilteredMutex);
    UnfilteredPlayers.clear();

    // [AG] get teams
    std::unordered_map<i32, i16> teams{};

    char* teamBuffer = nullptr;
    size_t teamSize = 0;
    std::string teamFile = AppConfig::settings().folderPath + "/team_data.csv";

    CsvUtils::load(teamFile.c_str(), &teamBuffer, teamSize);
    CsvUtils::interpretTeam(teams, teamBuffer, teamSize);

    // [AG] get players info
    char* masterBuffer = nullptr;
    size_t masterSize = 0;
    std::string masterFile = AppConfig::settings().folderPath + "/player_master.csv";

    CsvUtils::load(masterFile.c_str(), &masterBuffer, masterSize);
    CsvUtils::interpretMaster(teams, UnfilteredPlayers, masterBuffer, masterSize);

    // [AG] get players positions
    char* ratingsBuffer = nullptr;
    size_t ratingsSize = 0;
    std::string ratingsFile = AppConfig::settings().folderPath + "/player_ratings.csv";

    CsvUtils::load(ratingsFile.c_str(), &ratingsBuffer, ratingsSize);
    CsvUtils::interpretRatings(UnfilteredPlayers, ratingsBuffer, ratingsSize);

    // [AG] get players stats
    char* statsBuffer = nullptr;
    size_t statsSize = 0;
    std::string statsFile
      = AppConfig::settings().folderPath + "/player_skater_stats_rs.csv";

    CsvUtils::load(statsFile.c_str(), &statsBuffer, statsSize);
    CsvUtils::interpretStats(UnfilteredPlayers, statsBuffer, statsSize);
}
