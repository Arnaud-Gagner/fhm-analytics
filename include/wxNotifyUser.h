#ifndef WX_NOTIFY_USER
#define WX_NOTIFY_USER

#include <wx/msgdlg.h>

#define ASSERT(condition, msg)                                                           \
    if (!(condition)) {                                                                  \
        wxMessageBox(msg, "FATAL ERROR", wxOK | wxICON_ERROR);                           \
        std::terminate();                                                                \
    }

#define TERMINATE(msg)                                                                   \
    wxMessageBox(msg, "FATAL ERROR", wxOK | wxICON_ERROR);                               \
    std::terminate();

#define WARN(msg) wxMessageBox(msg, "WARNING", wxOK | wxICON_WARNING);

#endif // !WX_NOTIFY_USER
