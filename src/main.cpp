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

    char* buffer = nullptr;
    size_t bufferSize = 0;
    std::string file = AppConfig::settings().folderPath + "/boxscore_skater_summary.csv";

    CsvUtils::load(file.c_str(), &buffer, bufferSize);

    wxMainWindow* mainWindow = new wxMainWindow();
    mainWindow->Show();
    return true;
}
