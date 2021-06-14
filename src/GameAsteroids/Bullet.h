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

/**
 * An entity component which makes an entity a bullet.
 */
class Bullet : public astu::EntityComponent {
public:

    /**
     * Constructor.
     * 
     * @param maxDist   the maximum distance
     */
    Bullet(float maxDist) 
        : maxDistance(maxDist)
        , maxDistanceSquared(maxDist * maxDist)
    {
        // Intentionally left empty.
    }

    void SetMaxDistance(float d) {
        maxDistance = std::abs(d);
        maxDistanceSquared = maxDistance;
    }

    float GetMaxDistanceSquared() const { 
        return maxDistanceSquared;
    }

    float GetMaxDistance() const {
        return maxDistance;
    }

    void SetStartPosition(const astu::Vector2f p) {
        startPos = p;
    }

    const Vector2f& GetStartPosition() const {
        return 
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Gun>(*this);
    }

private:
    /** The maximum distance a bullet can trave in world units. */
    float maxDistance;

    /** The maximum distance a bullet can trave in world units, squared. */
    float maxDistanceSquared;

    /** The start position of this bullet. */
    astu::Vector2f startPos;

};