/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "GameEvents.h"
#include "Asteroid.h"

// AST Utilities includes
#include <EntityService.h>
#include <VertexBuffer2D.h>
#include <Service.h>
#include <SignalService.h>
#include <CameraService2D.h>

// C++ Standard Library includes
#include <memory>

class GameManager 
    : public astu::BaseService
    , private astu::SignalListener<GameEvent>
    , private astu::CameraClient2D
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
    std::shared_ptr<astu::Entity> CreateDebris();
    std::shared_ptr<astu::VertexBuffer2D> CreateShipMesh();
    std::shared_ptr<astu::VertexBuffer2D> CreateAsteroidMesh(float r);
    astu::Vector2f GetRandomSafePosition();

    void FirePlayerEvent();

    // Inherited via SignalListener<GameEvent>
    virtual bool OnSignal(const GameEvent & signal) override;        

};