#include "wxUtils.h"

void wxUtils::labelWidget(wxSizer* sizer, wxWindow* widget, const wxString& label)
{
    if (!sizer || !widget) {
        return;
    }
    wxBoxSizer* layout = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* text = new wxStaticText(widget->GetParent(), wxID_ANY, label);

    layout->Add(text, 0, wxALIGN_CENTER_VERTICAL);
    layout->Add(widget, 1, wxEXPAND | wxALL, 2);
    sizer->Add(layout, 0, wxEXPAND);
}