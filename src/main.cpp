#include <wx/app.h>

#include "AppConfig.h"
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

    wxMainWindow* mainWindow = new wxMainWindow();
    mainWindow->Show();
    return true;
}
