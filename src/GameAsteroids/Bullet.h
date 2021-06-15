/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// C++ Standard Library includes.
#include <cmath>

// AST Utilities includes
#include <EntityService.h>
#include <Vector2.h>

/**
 * An entity component which makes an entity a bullet.
 */
class Bullet : public astu::EntityComponent {
public:
    /** The time until the bullet gets destroyed, even without collision. */
    float ttl;

    /**
     * Constructor.
     * 
     * @param ttl   the maximum time to live
     */
    Bullet(float ttl) 
        : ttl(ttl)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Bullet>(*this);
    }
};