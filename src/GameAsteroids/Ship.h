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
    /** Identifies the player (useful in multiplayer mode). */
    int playerId;

    /** The torque to be applied when rotating the ship. */
    float torque;

    /** The thrust force used to move the ship. */
    float thrust;

    /**
     * Constructor.
     * 
     * @param spatial   the scene node branch represending the entity
     */
    Ship(int playerId, float torque, float thrust)
        : playerId(playerId)
        , torque(torque)
        , thrust(thrust)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<astu::EntityComponent> Clone() override {
        // We must create a deep copy of the branch of scene graph. */
        return std::make_shared<Ship>(*this);
    }
};