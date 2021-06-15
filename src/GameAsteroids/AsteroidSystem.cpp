/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// C++ Standard Library includes
#include <iostream>

// AST Utilities includes
#include <Keyboard.h>

// Local includes
#include "Asteroid.h"
#include "Pose2.h"
#include "Bullet.h"
#include "AsteroidSystem.h"

using namespace astu;
using namespace std;

const EntityFamily AsteroidSystem::FAMILY = EntityFamily::Create<Asteroid, Pose2>();

AsteroidSystem::AsteroidSystem(int updatePriority)
    : Service("Asteroid System")
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void AsteroidSystem::OnStartup()
{
    // Intentionally left empty.
}

void AsteroidSystem::OnShutdown()
{
    // Intentionally left empty.
}

bool AsteroidSystem::OnSignal(const CollisionEvent & signal)
{
    if (signal.entityA->HasComponent<Asteroid>()) {
        HandleCollision(*signal.entityA, *signal.entityB);
    } else if (signal.entityB->HasComponent<Asteroid>()) {
        HandleCollision(*signal.entityB, *signal.entityA);
    }

    // Do not consume collision events.
    return false;
}

void AsteroidSystem::HandleCollision(Entity& asteroidEntity, Entity & opponent)
{
    if (!opponent.HasComponent<Bullet>()) {
        // Asteroid only collide with bullets
        return;
    }

    auto &asteroid = asteroidEntity.GetComponent<Asteroid>();
    switch (asteroid.type) {
    case Asteroid::BIG:
        break;

    case Asteroid::MEDIUM:
        break;
        
    case Asteroid::SMALL:
        break;
    }

    GetEntityService().RemoveEntity(asteroidEntity);
}

