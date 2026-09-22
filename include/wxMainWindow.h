#ifndef WX_MAIN_WINDOW_H
#define WX_MAIN_WINDOW_H

#include <wx/frame.h>

class wxMainWindow : public wxFrame
{
public:
    wxMainWindow(wxWindow* parent = nullptr);
    ~wxMainWindow() = default;
};

#endif // !WX_MAIN_WINDOW_H
