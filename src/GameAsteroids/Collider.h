/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <ECS.h>

// C++ Standard Library includes.
#include <cmath>
#include <cstdint>


/**
 * An entity component which makes an entity collide (circle collider).
 */
class Collider : public astu::EntityComponent {
public:
    /* The radius of this circle collider. */
    float radius;

    /** The collision categories of this collider. */
    int_fast16_t categoryBits;

    /** The collision mask of this collider. */
    int_fast16_t collisionMask;

    /**
     * Constructor.
     * 
     * @param r             the radius
     * @param categories    the collision category bits
     * @param mask          the collision mask bits
     */
    Collider(float r, int_fast16_t categories = 0x0001, int_fast16_t mask = 0xffff) 
        : radius(r)
        , categoryBits(categories)
        , collisionMask(mask)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Collider>(*this);
    }
};