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
class Asteroid : public astu::EntityComponent {
public:

    enum Type {BIG, MEDIUM, SMALL};

    /** The type of this asteroid. */
    Type type;

    /**
     * Constructor.
     * 
     * @param type   the type of this asteroid.
     */
    Asteroid(Type type) 
        : type(type)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Asteroid>(*this);
    }
};