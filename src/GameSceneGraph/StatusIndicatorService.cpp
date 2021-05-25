// C++ Standard Library includes
#include <stdexcept>

// AST Utilities includes
#include <IWindowManager.h>

// Local includes
#include "StatusIndicatorService.h"

using namespace astu;
using namespace std;

StatusIndicatorService::StatusIndicatorService(const std::string & windowTitle)
    : BaseService("Status Indicator Service")
    , title(windowTitle)
{
    // Intentionally left empty
}

void StatusIndicatorService::SetWindowTitle(const std::string & title)
{
    this->title = title;
    if (GetStatus() == Service::Running) {
        UpdateTitle();
    }
}

void StatusIndicatorService::OnStartup()
{
    status.clear();
    UpdateTitle();
    ASTU_SERVICE(SignalService<string>).AddListener(*this);
}

void StatusIndicatorService::OnShutdown()
{
    ASTU_SERVICE(SignalService<string>).RemoveListener(*this);
}

bool StatusIndicatorService::OnSignal(const string & signal)
{
    status = signal;
    UpdateTitle();
    return false;
}

void StatusIndicatorService::UpdateTitle()
{
    if (status.empty()) {
        if (!title.empty()) {
            ASTU_SERVICE(IWindowManager).SetTitle(title);   
        }
    } else if (title.empty()) {
        ASTU_SERVICE(IWindowManager).SetTitle(status);   
    } else {
        ASTU_SERVICE(IWindowManager).SetTitle(title + " | " + status);   
    }
}
