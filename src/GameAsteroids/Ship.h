/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// C++ Standard Library includes
#include <memory>

// AST Utilities includes
#include <Scene2.h>
#include <EntityService.h>

class Ship : public astu::EntityComponent {
public:
    /** The maximum torque to be applied when rotating the ship. */
    float maxTorque;

    /** The maximum thrust force used to move the ship. */
    float maxThrust;

    /** The current torque. */
    float curTorque;

    /** The velocity used to reach the target torque. */
    float torqueSpeed;

    /**
     * Constructor.
     * 
     * @param thrust        the maximum thurst used for acceleration
     * @param torque        the maximum torque used for steering
     * @param torqueSpeed   the velocity used to reach the target torque
     */
    Ship(float thrust, float torque, float torqueSpeed)
        : maxTorque(torque)
        , maxThrust(thrust)
        , torqueSpeed(torqueSpeed)
        , curTorque(0)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<astu::EntityComponent> Clone() override {
        // We must create a deep copy of the branch of scene graph. */
        return std::make_shared<Ship>(*this);
    }
};