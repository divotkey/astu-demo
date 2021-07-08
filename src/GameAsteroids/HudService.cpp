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
    windowManager = ASTU_GET_SERVICE(IWindowManager);
    numUpdates = 0;
}

void HudService::OnShutdown()
{
    windowManager = nullptr;
}


bool HudService::OnSignal(const PlayerEvent & event)
{
    windowManager->SetTitle(windowTitle 
        + " | Updates " + to_string(++numUpdates)
        + " | Level " + to_string(event.level)
        + " | Asteroids " + to_string(event.asteroids));
    
    return false;
}
