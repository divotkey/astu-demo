/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <EntityService.h>
#include <Transform2.h>

/**
 * An entity component which describes the position and orientation
 * in world space.
 */
class Pose2 : public astu::EntityComponent {
public:
    /** The transformation. */
    astu::Transform2<float> transform;

    /**
     * Constructor.
     */
    Pose2() {
        transform.SetIdentity();
    }

    /**
     * Constructor.
     * 
     * @param x     the x-coordinate of the initial translation
     * @param y     the y-coordinate of the initial translation
     * @param phi   the angle of the initial rotation in radians
     */
    Pose2(float x, float y, float phi = 0) {
        transform.SetTranslation(x, y);
        transform.SetRotation(phi);
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Pose2>(*this);
    }
};