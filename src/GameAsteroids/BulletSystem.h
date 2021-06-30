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


class BulletSystem 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
    , private astu::TimeClient
    , private astu::SignalListener<CollisionEvent>
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    BulletSystem(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    /** Whether the gun should fire bullets. */
    bool firing;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via OneFamilyEntitySystem
    virtual void ProcessEntity(astu::Entity & entity) override;

    // Inherited via SignalListener<CollisionEvent>
    virtual bool OnSignal(const CollisionEvent & signal) override;  
};