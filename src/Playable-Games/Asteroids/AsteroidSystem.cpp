/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#include "AsteroidSystem.h"
#include "CAsteroid.h"
#include "CBullet.h"

// AST Utilities includes
#include <AstuMath.h>
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily AsteroidSystem::FAMILY = EntityFamily::Create<CAsteroid, CBody, CPose>();

AsteroidSystem::AsteroidSystem()
    : BaseService("Asteroid System")
    , OneFamilyEntitySystem(FAMILY)    
    , EntityListener(FAMILY)
{
    // Intentionally left empty.
}

void AsteroidSystem::OnStartup()
{
    // Intentionally left empty.
}

void AsteroidSystem::OnShutdown()
{
    // Intentionally left empty.
}

void AsteroidSystem::OnEntityAdded(shared_ptr<Entity> entity)
{
    auto& asteroid = entity->GetComponent<CAsteroid>();
    auto& body = entity->GetComponent<CBody>();

    float speed = Random::GetInstance().NextFloat(asteroid.minVelocity, asteroid.maxVelocity);
    body.SetLinearVelocity(Random::GetInstance().NextVector2f(speed));
}

bool AsteroidSystem::OnCollision(Entity& entityA, Entity& entityB)
{
    if (entityA.HasComponent<CAsteroid>()) {
        if (entityB.HasComponent<CBullet>()) {
            DestroyAsteroid(entityA);
        }
    }
    if (entityB.HasComponent<CAsteroid>()) {
        if (entityA.HasComponent<CBullet>()) {
            DestroyAsteroid(entityB);
        }
    }
    return false;
}

void AsteroidSystem::DestroyAsteroid(Entity& entity)
{
    GetEntityService().RemoveEntity(entity);
    const auto& pos = entity.GetComponent<CPose>().transform.GetTranslation();

    const auto& asteroid = entity.GetComponent<CAsteroid>();

    switch (asteroid.type) {
    case CAsteroid::Type::Big:
        EmitSignal(GameEvent(GameEvent::Type::BigAsteroidDestroyed, pos));
        break;

    case CAsteroid::Type::Medium:
        EmitSignal(GameEvent(GameEvent::Type::MediumAsteroidDestroyed, pos));
        break;

    case CAsteroid::Type::Small:
        EmitSignal(GameEvent(GameEvent::Type::SmallAsteroidDestroyed, pos));
        break;
    }
}
