/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <ECS.h>

/**
 * An entity component which fires projectiles (bullets).
 */
class Gun : public astu::EntityComponent {
public:
    /** The fire rate of this gun. */
    float roundsPerSecond;

    /** The remaining time until a new bullet can be emitted. */
    float cooldown;

    /** The speed of the fired projectiles. */
    float muzzleVelocity;

    /** The number of bullets fired. */
    unsigned int bulletsFired;

    /** The offset relativ to the entity position. */
    astu::Vector2f offset;

    /** The direction the gun in pointing in local space. */
    astu::Vector2f direction;

    /**
     * Constructor.
     * 
     * @param rps   rounds per second
     * @param mv    muzzle velocity
     */
    Gun(float rps, float mv, const astu::Vector2f offset = {0, 0}) 
        : roundsPerSecond(rps)
        , cooldown(0)
        , muzzleVelocity(mv) 
        , bulletsFired(0)
        , offset(offset)
        , direction(0, -1)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Gun>(*this);
    }
};