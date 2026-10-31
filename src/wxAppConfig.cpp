#include "wxAppConfig.h"

#include <wx/textctrl.h>

#include "AppConfig.h"
#include "wxUtils.h"

wxAppConfig::wxAppConfig(wxWindow* parent)
  : wxDialog(parent, wxID_ANY, "App Configuration")
  , mFolderPath{ new wxTextCtrl(this, wxID_ANY, "") }
  , mFreeAgentsPath{ new wxTextCtrl(this, wxID_ANY, "") }
  , mCsvSeparator{ new wxTextCtrl(this, wxID_ANY, "") }
  , mPositionThreshold{ new wxTextCtrl(this, wxID_ANY, "") }
  , mApply{ new wxButton(this, wxID_ANY, "Apply") }
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxUtils::labelWidget(mainSizer, mFolderPath, "Save Folder:");
    wxUtils::labelWidget(mainSizer, mFreeAgentsPath, "Free Agents Folder:");
    wxUtils::labelWidget(mainSizer, mCsvSeparator, "CSV Separator:");
    wxUtils::labelWidget(mainSizer, mPositionThreshold, "Position Threshold:");
    mainSizer->Add(mApply, wxEXPAND | wxALL, 5);

    SetSizerAndFit(mainSizer);

    AppConfig::setCallback([this](const AppConfig_t& config) { setConfig(config); });
    AppConfig::validate(AppConfig::settings());

    mApply->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { apply(); });
}

void wxAppConfig::setConfig(const AppConfig_t& config)
{
    mFolderPath->SetValue(config.folderPath);
    mFreeAgentsPath->SetValue(config.freeAgentsPath);
    mCsvSeparator->SetValue(config.csvSeparator);
    mPositionThreshold->SetValue(std::to_string(config.positionThreshold));
}

void wxAppConfig::apply()
{
    AppConfig_t config{};

    config.folderPath = mFolderPath->GetValue().ToStdString();
    config.freeAgentsPath = mFreeAgentsPath->GetValue().ToStdString();

    std::string csvSeparator = mCsvSeparator->GetValue().ToStdString();
    if (csvSeparator.size() > 1) {
        WARN("CSV Separator expects just one character. Only the first character will be "
             "treated");
    }
    config.csvSeparator = csvSeparator[0];

    int positionThreshold = 0;
    if (mPositionThreshold->GetValue().ToInt(&positionThreshold)) {
        config.positionThreshold = positionThreshold;
    }
    else {
        WARN("Position Threshold was invalid so the default value was saved.");
    }
    AppConfig::validate(config);
}
