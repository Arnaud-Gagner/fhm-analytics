#include <wx/app.h>

#include "AppConfig.h"
#include "CsvUtils.h"
#include "wxMainWindow.h"

class FhmAnalytics : public wxApp
{
public:
    FhmAnalytics() = default;

    bool OnInit() override;
};

wxIMPLEMENT_APP_NO_MAIN(FhmAnalytics);

int main(int argc, char** argv)
{
    return wxEntry(argc, argv);
}

bool FhmAnalytics::OnInit()
{
    AppConfig::load();

    // [AG] get teams
    Teams_t teams{};

    char* teamBuffer = nullptr;
    size_t teamSize = 0;
    std::string teamFile = AppConfig::settings().folderPath + "/team_data.csv";

    CsvUtils::load(teamFile.c_str(), &teamBuffer, teamSize);
    CsvUtils::interpretTeam(teams, teamBuffer, teamSize);

    // [AG] get players
    Players_t players{};

    // [AG] get players info
    char* masterBuffer = nullptr;
    size_t masterSize = 0;
    std::string masterFile = AppConfig::settings().folderPath + "/player_master.csv";

    CsvUtils::load(masterFile.c_str(), &masterBuffer, masterSize);
    CsvUtils::interpretMaster(teams, players, masterBuffer, masterSize);

    // [AG] get players positions
    char* ratingsBuffer = nullptr;
    size_t ratingsSize = 0;
    std::string ratingsFile = AppConfig::settings().folderPath + "/player_ratings.csv";

    CsvUtils::load(ratingsFile.c_str(), &ratingsBuffer, ratingsSize);
    CsvUtils::interpretRatings(players, ratingsBuffer, ratingsSize);

    // [AG] get players stats
    char* statsBuffer = nullptr;
    size_t statsSize = 0;
    std::string statsFile
      = AppConfig::settings().folderPath + "/player_skater_stats_rs.csv";

    CsvUtils::load(statsFile.c_str(), &statsBuffer, statsSize);
    CsvUtils::interpretStats(players, statsBuffer, statsSize);

    wxMainWindow* mainWindow = new wxMainWindow();
    mainWindow->Show();
    return true;
}
