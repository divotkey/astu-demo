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

class GameManager : public astu::BaseService {
public:

    /**
     * Constructor.
     */
    GameManager();

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

private:

    void RegisterEntityPrototypes();
    void DeregisterEntityPrototypes();
    void ConfigureGameWorld();
    void SpawnPlayer();
    std::shared_ptr<astu::Entity> CreateBigAsteroid();
    std::shared_ptr<astu::Entity> CreatePlayerShip();
    std::shared_ptr<astu::Entity> CreateBullet();
    std::shared_ptr<astu::VertexBuffer2> CreateShipMesh();
};