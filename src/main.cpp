#include <wx/app.h>

#include "FhmAnalytics.h"
#include "wxMainWindow.h"

class wxFhmAnalytics : public wxApp
{
public:
    wxFhmAnalytics() = default;

    bool OnInit() override;
};

wxIMPLEMENT_APP_NO_MAIN(wxFhmAnalytics);

int main(int argc, char** argv)
{
    return wxEntry(argc, argv);
}

bool wxFhmAnalytics::OnInit()
{
    FhmAnalytics::init();
    SetAppearance(wxAppBase::Appearance::System);

    wxMainWindow* mainWindow = new wxMainWindow();
    mainWindow->Show();
    mainWindow->setPlayers(FhmAnalytics::filteredPlayers());
    return true;
}
