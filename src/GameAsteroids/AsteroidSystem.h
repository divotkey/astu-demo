/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <UpdateService.h>
#include <EntitySystems.h>
#include <ITimeManager.h>

// Local includes
#include "CollisionSystem.h"


class AsteroidSystem 
    : public astu::OneFamilyEntitySystem
    , private astu::SignalListener<CollisionEvent>
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    AsteroidSystem(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via SignalListener<CollisionEvent>
    virtual bool OnSignal(const CollisionEvent & signal) override;  

    void HandleCollision(astu::Entity& asteroid, astu::Entity & opponent);
};