#include "wxPlayerGrid.h"

#include <wx/grid.h>
#include <wx/sizer.h>

#include "FhmAnalytics.h"

namespace
{
    wxString formatToi(u16 totalSeconds)
    {
        const u16 minutes = totalSeconds / 60;
        const u16 seconds = totalSeconds % 60;
        return wxString::Format("%u:%02u", minutes, seconds);
    }
}

wxPlayerGrid::wxPlayerGrid(wxWindow* parent)
  : wxPanel(parent)
  , mTable{ new wxGrid(this, wxID_ANY) }
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mTable->CreateGrid(0, 24);

    mTable->SetRowLabelSize(0);
    mTable->SetColLabelValue(0, "Name");
    mTable->SetColLabelValue(1, "GP");
    mTable->SetColLabelValue(2, "G");
    mTable->SetColLabelValue(3, "A");
    mTable->SetColLabelValue(4, "Pts");
    mTable->SetColLabelValue(5, "+/-");
    mTable->SetColLabelValue(6, "evATOI");
    mTable->SetColLabelValue(7, "ATOI");
    mTable->SetColLabelValue(8, "G60");
    mTable->SetColLabelValue(9, "A60");
    mTable->SetColLabelValue(10, "Pts60");
    mTable->SetColLabelValue(11, "Shot60");
    mTable->SetColLabelValue(12, "S%");
    mTable->SetColLabelValue(13, "Hit60");
    mTable->SetColLabelValue(14, "SB60");
    mTable->SetColLabelValue(15, "tkaDiff60");
    mTable->SetColLabelValue(16, "SF60");
    mTable->SetColLabelValue(17, "SFDiff60");
    mTable->SetColLabelValue(18, "GFDiff60");
    mTable->SetColLabelValue(19, "CFRel%");
    mTable->SetColLabelValue(20, "CFDiff60");
    mTable->SetColLabelValue(21, "IPP");
    mTable->SetColLabelValue(22, "ATT");
    mTable->SetColLabelValue(23, "DEF");

    mainSizer->Add(mTable, 1, wxEXPAND);

    SetSizerAndFit(mainSizer);

    FhmAnalytics::setCallBack([this](const std::vector<Player_t>& players) {
        CallAfter([this, players]() { setPlayers(players); });
    });
    // TODO:
    // wxEVT_GRID_LABEL_LEFT_CLICK
}

void wxPlayerGrid::setPlayers(const std::vector<Player_t>& players)
{
    mTable->BeginBatch();

    if (mTable->GetNumberRows() > 0) {
        mTable->DeleteRows(0, mTable->GetNumberRows());
    }
    mTable->AppendRows(static_cast<int>(players.size()));

    int row = 0;
    for (const Player_t& player : players) {
        const Info_t& info = player.info;
        const Stats_t& stat = player.stat;
        const CalcStats_t& calc = player.calc;
        const Percentiles_t& pct = player.percentile;

        const wxString name = wxString::Format("%s %s", info.firstName, info.lastName);

        mTable->SetCellValue(row, 0, name);
        mTable->SetCellValue(row, 1, wxString::Format("%u", stat.gp));
        mTable->SetCellValue(row, 2, wxString::Format("%u", stat.goal));
        mTable->SetCellValue(row, 3, wxString::Format("%u", stat.assist));
        mTable->SetCellValue(row, 4, wxString::Format("%u", calc.pt));
        mTable->SetCellValue(row, 5, wxString::Format("%d", stat.plusMinus));
        mTable->SetCellValue(row, 6, formatToi(calc.aevtoi));
        mTable->SetCellValue(row, 7, formatToi(calc.atoi));
        mTable->SetCellValue(row, 8, wxString::Format("%.2f", calc.goal60));
        mTable->SetCellValue(row, 9, wxString::Format("%.2f", calc.assist60));
        mTable->SetCellValue(row, 10, wxString::Format("%.2f", calc.pt60));
        mTable->SetCellValue(row, 11, wxString::Format("%.2f", calc.shot60));
        mTable->SetCellValue(row, 12, wxString::Format("%.2f", calc.shotPer));
        mTable->SetCellValue(row, 13, wxString::Format("%.2f", calc.hit60));
        mTable->SetCellValue(row, 14, wxString::Format("%.2f", calc.sb60));
        mTable->SetCellValue(row, 15, wxString::Format("%.2f", calc.tkaDiff60));
        mTable->SetCellValue(row, 16, wxString::Format("%.2f", stat.sf60));
        mTable->SetCellValue(row, 17, wxString::Format("%.2f", calc.sfDiff60));
        mTable->SetCellValue(row, 18, wxString::Format("%.2f", calc.gfDiff60));
        mTable->SetCellValue(row, 19, wxString::Format("%.2f", calc.cfDiff60));
        mTable->SetCellValue(row, 20, wxString::Format("%.2f", stat.cfRel));
        mTable->SetCellValue(row, 21, wxString::Format("%.2f", calc.ipp));
        mTable->SetCellValue(row, 22, wxString::Format("%.0f", pct.attackIndex));
        mTable->SetCellValue(row, 23, wxString::Format("%.0f", pct.defenseIndex));
        ++row;
    }
    mTable->EndBatch();
    mTable->AutoSizeColumns();
    Refresh();
    Layout();
}
