#ifndef WX_MAIN_WINDOW_H
#define WX_MAIN_WINDOW_H

#include <wx/frame.h>

#include "Player.h"

class wxAppConfig;
class wxPlayerGrid;

class wxMainWindow : public wxFrame
{
public:
    wxMainWindow();
    ~wxMainWindow() = default;

    void setPlayers(const std::unordered_map<u32, Player_t>& players);

private:
    void askNewFolderPath();

private:
    wxAppConfig* mAppConfigWidget;
    wxPlayerGrid* mPlayerGrid;
};

#endif // !WX_MAIN_WINDOW_H
