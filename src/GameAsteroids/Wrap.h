/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <ECS.h>

/**
 * An entity component which forces entities to remain within an retangular
 * area of the world.
 */
class Wrap : public astu::EntityComponent {
public:

    /**
     * Constructor.
     */
    Wrap() {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Wrap>(*this);
    }
};