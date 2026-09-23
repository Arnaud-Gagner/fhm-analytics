#include "wxMainWindow.h"

#include <wx/wx.h>

wxMainWindow::wxMainWindow()
  : wxFrame(nullptr, wxID_ANY, "fhm-analytics v0.4.0")
{
    Maximize(true);

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* configMenu = new wxMenu;
    wxMenuItem* modifyConfig = configMenu->Append(wxID_ANY, "Modify Config File\tCtrl+F");
    menuBar->Append(configMenu, "&Config");

    SetMenuBar(menuBar);

    Bind(
      wxEVT_MENU,
      [this](wxCommandEvent&) {
          // TODO
      },
      modifyConfig->GetId());
}
