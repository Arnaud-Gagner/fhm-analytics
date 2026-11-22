#ifndef WX_UTILS_H
#define WX_UTILS_H

#include <wx/wx.h>

#define ASSERT(condition, msg)                                                           \
    if (!(condition)) {                                                                  \
        wxMessageBox(msg, "FATAL ERROR", wxOK | wxICON_ERROR);                           \
        std::terminate();                                                                \
    }

#define TERMINATE(msg)                                                                   \
    wxMessageBox(msg, "FATAL ERROR", wxOK | wxICON_ERROR);                               \
    std::terminate();

#define WARN(msg) wxMessageBox(msg, "WARNING", wxOK | wxICON_WARNING);

namespace wxUtils
{
    void labelWidget(wxSizer* sizer, wxWindow* widget, const wxString& label);
}

#endif // !WX_UTILS_H
