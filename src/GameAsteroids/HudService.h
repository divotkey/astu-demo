/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "GameEvents.h"

// AST Utilities include
#include <Service.h>
#include <SignalService.h>
#include <IWindowManager.h>

// C++ Standard Library includes
#include <string>
#include <memory>

class HudService 
    : public astu::BaseService
    , public astu::SignalListener<PlayerEvent>
{
public:

    HudService(const std::string & title = "");

    // Inherited via BaseService
    virtual void OnStartup() override; 
    virtual void OnShutdown() override; 

    // Inherited via SignalListener
    virtual bool OnSignal(const PlayerEvent & event) override;

private:
    /** The main title of the window. */
    const std::string windowTitle;

    int numUpdates;

    /** Used to update the window title. */
    std::shared_ptr<astu::IWindowManager> windowManager;
};