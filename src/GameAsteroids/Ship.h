/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <ECS.h>
#include <Suite2D.h>
#include <AstuMath.h>

// C++ Standard Library includes
#include <memory>

class Ship : public astu::EntityComponent {
public:
    /** The maximum torque to be applied when rotating the ship. */
    float maxTorque;

    /** The maximum thrust force used to move the ship. */
    float maxThrust;

    /** Used to ease thrust input. */
    astu::LinearInterpolator1f thrustInput;
    
    /** Used to ease steering input. */
    astu::LinearInterpolator1f steeringInput;

    /**
     * Constructor.
     * 
     * @param thrust        the maximum thurst used for acceleration
     * @param torque        the maximum torque used for steering
     * @param steerSpeed    controls the ease of steering input
     * @param thrustSpeed   controls the ease of thrust input
     */
    Ship(float thrust, float torque, float steerSpeed, float thrustSpeed)
        : maxTorque(torque)
        , maxThrust(thrust)
        , steeringInput(steerSpeed)
        , thrustInput(thrustSpeed)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<astu::EntityComponent> Clone() override {
        // We must create a deep copy of the branch of scene graph. */
        return std::make_shared<Ship>(*this);
    }
};