/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <Services.h>
#include <AstuInput.h>
#include <ECS.h>

class FadeSystem 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
    , private astu::TimeClient
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    FadeSystem(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via OneFamilyEntitySystem
    virtual void ProcessEntity(astu::Entity & entity) override;
};