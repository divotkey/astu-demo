/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuMath.h>
#include <ECS.h>

class WrapSystem 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    WrapSystem(int updatePriority = 0);

    void SetWrapSize(float w, float h);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    /** The upper left corner of the wrap area. */
    astu::Vector2f upperLeft;

    /** The lower right corner of the wrap area. */
    astu::Vector2f lowerRight;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via OneFamilyEntitySystem
    virtual void ProcessEntity(astu::Entity & entity) override;
};