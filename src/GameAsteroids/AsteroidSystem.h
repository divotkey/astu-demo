/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "CollisionSystem.h"
#include "Asteroid.h"

// AST Utilities includes
#include <Services.h>
#include <ECS.h>


class AsteroidSystem 
    : public astu::OneFamilyEntitySystem
    , private astu::EntityListener
    , private astu::SignalListener<CollisionEvent>
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    AsteroidSystem(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    /** Determines the number of smaller asteroids to spawn. */
    unsigned int numDebrisAsteroids;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;



    // Inherited via EntityListener
    virtual void OnEntityAdded(std::shared_ptr<astu::Entity> entity) override;

    // Inherited via SignalListener<CollisionEvent>
    virtual bool OnSignal(const CollisionEvent & signal) override;  

    void HandleCollision(astu::Entity& asteroid, astu::Entity & opponent);
    void SpawnAsteroid(const astu::Vector2f & p, Asteroid::Type type);
};