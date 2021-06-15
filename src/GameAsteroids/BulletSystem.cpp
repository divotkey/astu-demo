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
#include "Bullet.h"
#include "Pose2.h"
#include "BulletSystem.h"

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
        GetEntityService().RemoveEntity(signal.entityA);
    }

    if (signal.entityB->HasComponent<Bullet>()) {
        GetEntityService().RemoveEntity(signal.entityB);
    }

    // Do not consume collision events.
    return false;
}

