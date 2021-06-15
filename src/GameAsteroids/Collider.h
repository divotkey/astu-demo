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
 * An entity component which makes an entity collide (circle collider).
 */
class Collider : public astu::EntityComponent {
public:
    /* The radius of this circle collider. */
    float radius;

    /**
     * Constructor.
     * 
     * @param r   the radius
     */
    Collider(float r) 
        : radius(r)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Collider>(*this);
    }
};