#include "wxMainWindow.h"

#include <wx/wx.h>

#include "AppConfig.h"
#include "wxAppConfig.h"

wxMainWindow::wxMainWindow()
  : wxFrame(nullptr, wxID_ANY, "fhm-analytics v0.4.0")
  , mAppConfigWidget{ new wxAppConfig(this) }
{
    Maximize(true);

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* configMenu = new wxMenu;
    wxMenuItem* folderPath = configMenu->Append(wxID_ANY, "Change Folder Path\tCtrl+O");
    wxMenuItem* modifyConfig = configMenu->Append(wxID_ANY, "Modify Config File\tCtrl+F");
    menuBar->Append(configMenu, "&Config");

    SetMenuBar(menuBar);

    Bind(
      wxEVT_MENU, [this](wxCommandEvent&) { askNewFolderPath(); }, folderPath->GetId());
    Bind(
      wxEVT_MENU,
      [this](wxCommandEvent&) { mAppConfigWidget->Show(); },
      modifyConfig->GetId());
}

void wxMainWindow::askNewFolderPath()
{
    wxDirDialog directoryDialog(
      NULL, "Pick Your Save Folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (directoryDialog.ShowModal() != wxID_OK) {
        return;
    }
    std::string path = directoryDialog.GetPath().ToStdString();
    std::replace(path.begin(), path.end(), '\\', '/');

    AppConfig_t config = AppConfig::settings();
    config.folderPath = path;
    AppConfig::validate(config);
}
