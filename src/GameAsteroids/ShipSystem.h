/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuMath.h>
#include <Services.h>
#include <AstuInput.h>
#include <Suite2D.h>
#include <ECS.h>

// C++ Standard Library includes
#include <memory>

class ShipSystem 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
    , private astu::TimeClient
    , private astu2d::LineRendererClient2f
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    ShipSystem(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    /** The axis used to accelerate the space ship. */
    std::shared_ptr<astu::AxisBinding> thrustAxis;

    /** The axis used to steer the space ship. */
    std::shared_ptr<astu::AxisBinding> steerAxis;

    /** Used to create thrust particle entities. */
    std::shared_ptr<astu::EntityFactoryService> entityFactory;

    /** Draws the current state of the input axis for debugging. */
    void DrawAxesState(astu::LinearInterpolator1f & hAxis, astu::LinearInterpolator1f & vAxis);

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via OneFamilyEntitySystem
    virtual void ProcessEntity(astu::Entity & entity) override;
};