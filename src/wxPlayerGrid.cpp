#include "wxPlayerGrid.h"

#include <wx/grid.h>
#include <wx/sizer.h>

wxPlayerGrid::wxPlayerGrid(wxWindow* parent)
  : wxPanel(parent)
  , mTable{ new wxGrid(this, wxID_ANY) }
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    SetSizer(mainSizer);
}
