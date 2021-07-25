/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// C++ Standard Library includes
#include <iostream>

// AST Utilities includes
#include <AstUtils.h>
#include <ECS.h>
#include <Suite2D.h>

// Local includes
#include "Body2.h"
#include "Bullet.h"
#include "GameEvents.h"
#include "AsteroidSystem.h"

using namespace astu2d;
using namespace astu;
using namespace std;

#define DEFAULT_NUM_DEBRIS_ASTEROIDS 2

// This macro signals a game event; helps to improve readability.
#define GAME_EVENT(type, pos) ASTU_SERVICE(SignalService<GameEvent>).QueueSignal(GameEvent(type, pos))

const EntityFamily AsteroidSystem::FAMILY = EntityFamily::Create<Asteroid, CPose, Body2>();

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
    float av = GetRandomFloat(asteroid.maxAngVel, asteroid.minAngVel);
    if (GetRandomBool()) {
        av = -av;
    }
    body.SetAngularVelocity(av);
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

    const auto & pos = asteroidEntity.GetComponent<CPose>().transform.GetTranslation();

    auto &asteroid = asteroidEntity.GetComponent<Asteroid>();
    switch (asteroid.type) {
    case Asteroid::BIG:

        for (unsigned int i = 0; i < numDebrisAsteroids; ++i) {
            SpawnAsteroid(pos, Asteroid::MEDIUM);
        }

        GAME_EVENT(GameEvent::BIG_ASTEROID_DESTROYED, pos);
        break;

    case Asteroid::MEDIUM:
        for (unsigned int i = 0; i < numDebrisAsteroids; ++i) {
            SpawnAsteroid(pos, Asteroid::SMALL);
        }

        GAME_EVENT(GameEvent::MEDIUM_ASTEROID_DESTROYED, pos);
        break;
        
    case Asteroid::SMALL:
        GAME_EVENT(GameEvent::SMALL_ASTEROID_DESTROYED, pos);
        break;
    }

    GetEntityService().RemoveEntity(asteroidEntity);
}

void AsteroidSystem::SpawnAsteroid(const astu::Vector2f & p, Asteroid::Type type)
{
    std::shared_ptr<Entity> entity;

    switch (type) {

    case Asteroid::BIG:
        GAME_EVENT(GameEvent::BIG_ASTEROID_SPAWNED, p);
        entity = ASTU_SERVICE(EntityFactoryService)
            .CreateEntity("BigAsteroid");
        break;

    case Asteroid::MEDIUM:
        GAME_EVENT(GameEvent::MEDIUM_ASTEROID_SPAWNED, p);
        entity = ASTU_SERVICE(EntityFactoryService)
            .CreateEntity("MediumAsteroid");
        break;

    case Asteroid::SMALL:
        GAME_EVENT(GameEvent::SMALL_ASTEROID_SPAWNED, p);
        entity = ASTU_SERVICE(EntityFactoryService)
            .CreateEntity("SmallAsteroid");
        break;

    default:
        throw std::logic_error("Asteroid type unknown: " + std::to_string(type));
    }

    // Set position.
    entity->GetComponent<CPose>().transform.SetTranslation(p);

    // Add entity to the game world.
    GetEntityService().AddEntity(entity);
}