/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "HudService.h"

using namespace astu;
using namespace std;

HudService::HudService(const std::string & title)
    : Service("HUD Service")
    , windowTitle(title)
{
    // Intentinoally left empty.
}

void HudService::OnStartup()
{
    windowService = ASTU_GET_SERVICE(WindowService);
}

void HudService::OnShutdown()
{
    windowService = nullptr;
}

bool HudService::OnSignal(const PlayerEvent & event)
{
    windowService->SetTitle(windowTitle 
        + " | Score " + to_string(event.score)
        + " | Level " + to_string(event.level)
        + " | Asteroids " + to_string(event.asteroids));
    
    return false;
}
