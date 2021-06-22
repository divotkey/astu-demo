/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// C++ Standard Library includes
#include <iostream>

// AST Utilities includes
#include <AstUtils.h>
#include <EntityFactoryService.h>

// Local includes
#include "Pose2.h"
#include "Body2.h"
#include "Bullet.h"
#include "GameEvents.h"
#include "AsteroidSystem.h"

using namespace astu;
using namespace std;

#define DEFAULT_NUM_DEBRIS_ASTEROIDS 2

const EntityFamily AsteroidSystem::FAMILY = EntityFamily::Create<Asteroid, Pose2, Body2>();

AsteroidSystem::AsteroidSystem(int updatePriority)
    : Service("Asteroid System")
    , OneFamilyEntitySystem(FAMILY)
    , EntityListener(FAMILY)
    , numDebrisAsteroids(DEFAULT_NUM_DEBRIS_ASTEROIDS)
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

void AsteroidSystem::OnEntityAdded(std::shared_ptr<astu::Entity> entity)
{
    auto &asteroid = entity->GetComponent<Asteroid>();
    auto &body = entity->GetComponent<Body2>();

    // Set random linear velocity.
    Vector2f v(0, GetRandomFloat(asteroid.maxLinVel, asteroid.minLinVel));
    v.RotateDeg(GetRandomFloat(0, 360));
    body.SetLinearVelocity(v);

    // Set random angular velocity.
    body.SetAngularVelocity(GetRandomFloat(asteroid.maxAngVel, asteroid.minAngVel));
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

    const auto & pos = asteroidEntity.GetComponent<Pose2>().transform.GetTranslation();

    auto &asteroid = asteroidEntity.GetComponent<Asteroid>();
    switch (asteroid.type) {
    case Asteroid::BIG:
        ASTU_SERVICE(SignalService<GameEvent>)
            .QueueSignal(GameEvent(GameEvent::BIG_ASTEROID_DESTROYED, pos));

        for (unsigned int i = 0; i < numDebrisAsteroids; ++i) {
            SpawnAsteroid(pos, Asteroid::MEDIUM);
        }
        break;

    case Asteroid::MEDIUM:
        ASTU_SERVICE(SignalService<GameEvent>)
            .QueueSignal(GameEvent(GameEvent::MEDIUM_ASTEROID_DESTROYED, pos));
        for (unsigned int i = 0; i < numDebrisAsteroids; ++i) {
            SpawnAsteroid(pos, Asteroid::SMALL);
        }
        break;
        
    case Asteroid::SMALL:
        ASTU_SERVICE(SignalService<GameEvent>)
            .QueueSignal(GameEvent(GameEvent::SMALL_ASTEROID_DESTROYED, pos));
        break;
    }

    GetEntityService().RemoveEntity(asteroidEntity);
}

void AsteroidSystem::SpawnAsteroid(const astu::Vector2f & p, Asteroid::Type type)
{
    std::shared_ptr<Entity> entity;

    switch (type) {

    case Asteroid::BIG:
        ASTU_SERVICE(SignalService<GameEvent>)
            .QueueSignal(GameEvent(GameEvent::BIG_ASTEROID_SPAWNED, p));
        entity = ASTU_SERVICE(EntityFactoryService)
            .CreateEntity("BigAsteroid");
        break;

    case Asteroid::MEDIUM:
        ASTU_SERVICE(SignalService<GameEvent>)
            .QueueSignal(GameEvent(GameEvent::MEDIUM_ASTEROID_SPAWNED, p));
        entity = ASTU_SERVICE(EntityFactoryService)
            .CreateEntity("MediumAsteroid");
        break;

    case Asteroid::SMALL:
        ASTU_SERVICE(SignalService<GameEvent>)
            .QueueSignal(GameEvent(GameEvent::SMALL_ASTEROID_SPAWNED, p));
        entity = ASTU_SERVICE(EntityFactoryService)
            .CreateEntity("SmallAsteroid");
        break;

    default:
        throw std::logic_error("Ateroid type unknown");
    }

    // Set position.
    entity->GetComponent<Pose2>().transform.SetTranslation(p);

    // Add entity to the game world.
    GetEntityService().AddEntity(entity);
}