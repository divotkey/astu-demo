/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// C++ Standard Library includes
#include <memory>

// AST Utilities includes
#include <EntityService.h>
#include <VertexBuffer2.h>
#include <Service.h>
#include <SignalService.h>

// Local includes
#include "GameEvents.h"
#include "Asteroid.h"

class GameManager 
    : public astu::BaseService
    , private astu::SignalListener<GameEvent>
{
public:

    /**
     * Constructor.
     */
    GameManager();

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

private:
    /** The current level, which defines score, number of asteroids, etc. */
    int curLevel;

    /** The current number of asteroids left. */
    int numAsteroids;

    /** Used to signal palyer event. */
    std::shared_ptr<astu::SignalService<PlayerEvent>> playerEvents;

    void RegisterEntityPrototypes();
    void DeregisterEntityPrototypes();
    void ConfigureGameWorld();
    void SpawnPlayer();
    void SpawnAsteroids();
    void SpawnAsteroid(const astu::Vector2f & p);
    std::shared_ptr<astu::Entity> CreateAsteroid(Asteroid::Type type, float radius);
    std::shared_ptr<astu::Entity> CreatePlayerShip();
    std::shared_ptr<astu::Entity> CreateBullet();
    std::shared_ptr<astu::VertexBuffer2> CreateShipMesh();
    std::shared_ptr<astu::VertexBuffer2> CreateAsteroidMesh(float r);
    astu::Vector2f GetRandomSafePosition();

    void FirePlayerEvent();

    // Inherited via SignalListener<GameEvent>
    virtual bool OnSignal(const GameEvent & signal) override;        

};