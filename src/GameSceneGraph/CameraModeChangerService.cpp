// Local includes
#include "CameraModeChangerService.h"

// AST-Utilities includes
#include <Services.h>

// C++ Standard Library includes
#include <iostream>
#include <string>


using namespace astu;
using namespace std;

CameraModeChangerService::CameraModeChangerService()
    : Service("Camera Mode Changer Service")
    , switchKey(Keyboard::KEY_C)
    , viewWidth(0)
    , viewHeight(0)
{
    // Intentionally left empty.
}

void CameraModeChangerService::OnStartup()
{
    mode = Mode::Screen;

    // Fallback to screen dimensions if no view area is specified.
    if (viewWidth <= 0) {
        viewWidth = 
            static_cast<float>( ASTU_SERVICE(WindowService).GetWidth() );
    }
    if (viewHeight <= 0) {
        viewHeight = 
            static_cast<float>( ASTU_SERVICE(WindowService).GetHeight() );
    }

    UpdateCameraMode();
}

void CameraModeChangerService::OnShutdown()
{
    // Intentionally left empty.
}

bool CameraModeChangerService::OnKeyPressed(int keycode)
{
    if (keycode != Keyboard::KEY_C) {
        return false;
    }

    switch (mode) {
    case Screen:
        mode = FixedWidth;
        break;
    
    case FixedWidth:
        mode = FixedHeight;
        break;

    case FixedHeight:
        mode = Fitting;
        break;

    case Fitting:
        mode = Filling;
        break;

    case Filling:
        mode = Streched;
        break;

    case Streched:
        mode = Screen;
        break;

    default:
        // Fallback
        mode = Screen;
        break;
    }

    UpdateCameraMode();
    return true;
}

CameraModeChangerService& CameraModeChangerService::SetViewSize(float w, float h)
{
    viewWidth = w;
    viewHeight = h;
    return *this;
}

void CameraModeChangerService::UpdateCameraMode()
{
    switch (mode) {
    case Screen:
        GetCamera().ShowScreenSpace();
        UpdateStatus("Camera Mode: Screen Space");
        break;
    
    case FixedWidth:
        GetCamera().ShowFixedWidth(viewWidth);
        UpdateStatus("Camera Mode: Fixed Width "); 
        break;

    case FixedHeight:
        GetCamera().ShowFixedHeight(viewHeight);
        UpdateStatus("Camera Mode: Fixed Height");
        break;

    case Fitting:
        GetCamera().ShowFitting(viewWidth, viewHeight);
        UpdateStatus("Camera Mode: Fitting");
        break;

    case Filling:
        GetCamera().ShowFilling(viewWidth, viewHeight);
        UpdateStatus("Camera Mode: Filling");
        break;

    case Streched:
        GetCamera().ShowStreched(viewWidth, viewHeight);
        UpdateStatus("Camera Mode: Streched");
        break;

    default:
        break;
    }
}

void CameraModeChangerService::UpdateStatus(const std::string & msg)
{
    ASTU_SERVICE(SignalService<string>).QueueSignal(msg);
}

