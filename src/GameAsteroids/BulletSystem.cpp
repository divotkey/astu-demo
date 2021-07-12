/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "BulletSystem.h"
#include "Bullet.h"
#include "Pose2.h"
#include "Body2.h"

// AST Utilities includes
#include <AstUtils.h>
#include <EntityFactoryService.h>

// C++ Standard Library includes
#include <iostream>

using namespace astu;
using namespace std;

const EntityFamily BulletSystem::FAMILY = EntityFamily::Create<Bullet, Pose2>();

BulletSystem::BulletSystem(int updatePriority)
    : Service("Bullet System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void BulletSystem::OnStartup()
{
    // Intentionally left empty.
}

void BulletSystem::OnShutdown()
{
    // Intentionally left empty.
}

void BulletSystem::OnUpdate()
{
    ProcessEntities();
}

void BulletSystem::ProcessEntity(Entity & entity)
{
    auto & pose = entity.GetComponent<Pose2>();
    auto & bullet = entity.GetComponent<Bullet>();

    bullet.ttl -= GetElapsedTimeF();
    if (bullet.ttl < 0) {
        GetEntityService().RemoveEntity(entity);
    }

}

bool BulletSystem::OnSignal(const CollisionEvent & signal)
{
    if (signal.entityA->HasComponent<Bullet>()) {
        OnCollision(*signal.entityA);
    }

    if (signal.entityB->HasComponent<Bullet>()) {
        OnCollision(*signal.entityB);
    }

    // Do not consume collision events.
    return false;
}

void BulletSystem::OnCollision(Entity & e)
{
    GetEntityService().RemoveEntity(e);
    const auto &p = e.GetComponent<Pose2>().transform.GetTranslation();
    for (int i = 0; i < GetRandomInt(3, 7); ++i) {
        EmitDebris(p);
    }
}

void BulletSystem::EmitDebris(const astu::Vector2f& p)
{
    auto entity = ASTU_SERVICE(EntityFactoryService).CreateEntity("Debris");
    entity->GetComponent<Pose2>().transform.SetTranslation(p);
    auto &body = entity->GetComponent<Body2>();

    // Set random angular velocity.
    float av = GetRandomFloat(0.25, 2.0);
    if (GetRandomBool()) {
        av *= -1;
    }
    body.SetAngularVelocity(av);

    // Set random linear velocity.
    Vector2f v(0, GetRandomFloat(1, 2));
    v.Rotate(GetRandomFloat(0, MathUtils::PI2f));
    body.SetLinearVelocity(v);
    
    GetEntityService().AddEntity(entity);
}
