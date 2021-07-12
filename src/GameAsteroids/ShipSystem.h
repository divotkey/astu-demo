/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <EntityFactoryService.h>
#include <UpdateService.h>
#include <EntitySystems.h>
#include <InputMappingService.h>
#include <ITimeManager.h>
#include <ILineRenderer.h>
#include <Interpolator.h>

// C++ Standard Library includes
#include <memory>

class ShipSystem 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
    , private astu::TimeClient
    , private astu::LineRendererClient<float>
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

    /** Interpolator used to ease thrust input. */
    astu::LinearInterpolator1f thrustInput;

    /** Interpolator used to ease steering input. */
    astu::LinearInterpolator1f steerInput;

    void DrawAxesState(astu::LinearInterpolator1f & hAxis, astu::LinearInterpolator1f & vAxis);

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via OneFamilyEntitySystem
    virtual void ProcessEntity(astu::Entity & entity) override;
};