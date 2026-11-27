#include "FhmAnalytics.h"

#include <mutex>
#include <vector>

#include "AppConfig.h"
#include "CsvUtils.h"
#include "FilterConfig.h"
#include "GroupStats.h"
#include "Player.h"

namespace
{
    std::unordered_map<u32, Player_t> UnfilteredPlayers{};
    std::mutex UnfilteredMutex;

    std::vector<Player_t> FilteredPlayers = {};
    std::mutex FilteredMutex;

    std::function<void(std::vector<Player_t>&)> RefreshPlayers = {};

    void reloadTeams(bool isFreeAgents)
    {
        char* masterBuffer = nullptr;
        size_t masterSize = 0;

        std::string masterFile;
        isFreeAgents ? masterFile = AppConfig::settings().freeAgentsPath
                     : masterFile = AppConfig::settings().folderPath;
        masterFile += "/player_master.csv";

        CsvUtils::load(masterFile.c_str(), &masterBuffer, masterSize);
        CsvUtils::updatePlayerTeam(UnfilteredPlayers, masterBuffer, masterSize);
        free(masterBuffer);
    }
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
    free(teamBuffer);

    // [AG] get players info
    char* masterBuffer = nullptr;
    size_t masterSize = 0;
    std::string masterFile = AppConfig::settings().folderPath + "/player_master.csv";

    CsvUtils::load(masterFile.c_str(), &masterBuffer, masterSize);
    CsvUtils::interpretMaster(teams, UnfilteredPlayers, masterBuffer, masterSize);
    free(masterBuffer);

    // [AG] get players positions
    char* ratingsBuffer = nullptr;
    size_t ratingsSize = 0;
    std::string ratingsFile = AppConfig::settings().folderPath + "/player_ratings.csv";

    CsvUtils::load(ratingsFile.c_str(), &ratingsBuffer, ratingsSize);
    CsvUtils::interpretRatings(UnfilteredPlayers, ratingsBuffer, ratingsSize);
    free(ratingsBuffer);

    // [AG] get players stats
    char* statsBuffer = nullptr;
    size_t statsSize = 0;
    std::string statsFile
      = AppConfig::settings().folderPath + "/player_skater_stats_rs.csv";

    CsvUtils::load(statsFile.c_str(), &statsBuffer, statsSize);
    CsvUtils::interpretStats(UnfilteredPlayers, statsBuffer, statsSize);
    free(statsBuffer);

    applyFilter();
}

void FhmAnalytics::loadTeams(bool isFA)
{
    reloadTeams(isFA);
    applyFilter();
}

void FhmAnalytics::applyFilter()
{
    std::unique_lock<std::mutex> lock(FilteredMutex);

    PlayerGroup_t attack{};
    PlayerGroup_t defense{};
    for (auto& [id, player] : UnfilteredPlayers) {
        if (player.info.leagueId == 0 && player.stat.gp >= 10
            && (player.position.c == 20 || player.position.lw == 20
                || player.position.rw == 20)) {
            Player::calcStats(player);
            attack.players.push_back(&player);
        }
        if (player.info.leagueId == 0 && player.stat.gp >= 10
            && (player.position.ld == 20 || player.position.rd == 20)) {
            Player::calcStats(player);
            defense.players.push_back(&player);
        }
    }
    GroupStats::loadPercentiles(attack);
    GroupStats::loadPercentiles(defense);

    FilteredPlayers = {};
    for (Player_t* player : attack.players) {
        Player::indexes(player);
    }
    for (Player_t* player : defense.players) {
        Player::indexes(player);
    }
    GroupStats::loadIndexPercentiles(attack);
    GroupStats::loadIndexPercentiles(defense);

    for (Player_t* player : attack.players) {
        if (player->info.teamId == 25) {
            FilteredPlayers.push_back(*player);
        }
    }
    for (Player_t* player : defense.players) {
        if (player->info.teamId == 25) {
            FilteredPlayers.push_back(*player);
        }
    }
    if (RefreshPlayers) {
        RefreshPlayers(FilteredPlayers);
    }
}

const std::vector<Player_t>& FhmAnalytics::filteredPlayers()
{
    std::unique_lock<std::mutex> lock(FilteredMutex);
    return FilteredPlayers;
}

void FhmAnalytics::setCallBack(
  const std::function<void(const std::vector<Player_t>&)>& callback)
{
    RefreshPlayers = std::move(callback);
}
