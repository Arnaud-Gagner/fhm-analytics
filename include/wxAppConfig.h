#ifndef WX_APP_CONFIG_H
#define WX_APP_CONFIG_H

#include <wx/dialog.h>

#include "AppConfig.h"

class wxTextCtrl;

class wxAppConfig : public wxDialog
{
public:
    wxAppConfig(wxWindow* parent = nullptr);
    ~wxAppConfig() = default;

    void setConfig(const AppConfig_t& config);

private:
    void apply();

private:
    wxTextCtrl* mFolderPath;
    wxTextCtrl* mFreeAgentsPath;
    wxTextCtrl* mCsvSeparator;
    wxTextCtrl* mPositionThreshold;

    wxButton* mApply;
};

#endif // !WX_APP_CONFIG_H
