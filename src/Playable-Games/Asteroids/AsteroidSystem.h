/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */


#pragma once

// Local includes
#include "GameEvent.h"

// AST Utilities includes
#include <AstuServices.h>
#include <AstuECS.h>
#include <AstuSuite2D.h>

class AsteroidSystem 
    : public astu::BaseService
    , private astu::OneFamilyEntitySystem
    , private astu::EntityListener
    , private astu::SignalEmitter<GameEvent>
    , private astu2d::CollisionListener
{
public:

    /** Constructor. */
    AsteroidSystem();

private:
    // The family of entities this system processes
    static const astu::EntityFamily FAMILY;

    /**
     * Destroys the asteroid entity.
     * 
     * @param entity    the asteroid entity
     */
    void DestroyAsteroid(astu::Entity& entity);

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via EntityListener
    virtual void OnEntityAdded(std::shared_ptr<astu::Entity> entity) override;

    // Inherited via CollisionListener
    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;
};