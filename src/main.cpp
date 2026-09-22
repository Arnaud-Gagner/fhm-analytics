#include <wx/app.h>
#include <wx/display.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/splash.h>
#include <wx/stdpaths.h>

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
    wxMainWindow* mainWindow = new wxMainWindow();
    mainWindow->Show();
    return true;
}
