/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// C++ Standard Library includes.
#include <cmath>

// AST Utilities includes
#include <AstuMath.h>
#include <ECS.h>

/**
 * An entity component which makes an entity a bullet.
 */
class Asteroid : public astu::EntityComponent {
public:

    enum Type {BIG, MEDIUM, SMALL};

    /** The type of this asteroid. */
    Type type;

    /** The maximum linear velocity. */
    float maxLinVel;

    /** The minimum linear velocity. */
    float minLinVel;

    /** The maximum angular velocity. */
    float maxAngVel;

    /** The minimum angular velocity. */
    float minAngVel;

    /**
     * Constructor.
     * 
     * @param type      the type of this asteroid
     * @param maxLinVel maximum linear velocity
     * @param minLinVel maximum linear velocity
     * @param maxAngVel maximum angular velocity
     * @param minAngVel minimum angular velocity
     */
    Asteroid(Type type, float maxLinVel, float minLinVel, float maxAngVel, float minAngVel) 
        : type(type)
        , maxLinVel(maxLinVel)
        , minLinVel(minLinVel)
        , maxAngVel(maxAngVel)
        , minAngVel(minAngVel)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Asteroid>(*this);
    }
};