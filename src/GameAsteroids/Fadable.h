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
class Fadable : public astu::EntityComponent {
public:
    /** The fade duration in seconds. */
    float duration;

    /** The elapsed time in seconds. */
    float elapsed;

    /**
     * Constructor.
     * 
     * @param duration  the fade duration in seconds
     */
    Fadable(float duration) 
        : duration(duration)
        , elapsed(0)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Fadable>(*this);
    }
};