#ifndef WX_MAIN_WINDOW_H
#define WX_MAIN_WINDOW_H

#include <wx/frame.h>

class wxAppConfig;

class wxMainWindow : public wxFrame
{
public:
    wxMainWindow();
    ~wxMainWindow() = default;

private:
    void askNewFolderPath();

private:
    wxAppConfig* mAppConfigWidget;
};

#endif // !WX_MAIN_WINDOW_H
