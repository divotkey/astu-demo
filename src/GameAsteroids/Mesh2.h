/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <Scene2D.h>
#include <EntityService.h>

// C++ Standard Library includes
#include <memory>

class Mesh2 : public astu::EntityComponent {
public:
    /** Branch of the scene graph representing this component's entity. */
    std::shared_ptr<astu::Spatial2D> spatial;

    /**
     * Constructor.
     * 
     * @param spatial   the scene node branch represending the entity
     */
    Mesh2(std::shared_ptr<astu::Spatial2D> spatial)
        : spatial(spatial)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<astu::EntityComponent> Clone() override {
        // We must create a deep copy of the branch of scene graph. */
        return std::make_shared<Mesh2>( spatial->Clone() );
    }
};