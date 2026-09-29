#ifndef WX_PLAYER_GRID_H
#define WX_PLAYER_GRID_H

#include <wx/panel.h>

#include "Player.h"

class wxGrid;

class wxPlayerGrid : public wxPanel
{
public:
    wxPlayerGrid(wxWindow* parent = nullptr);
    ~wxPlayerGrid() = default;

    void setPlayers(const std::vector<Player_t>& players);

private:
    wxGrid* mTable;
};

#endif // !WX_PLAYER_GRID_H
