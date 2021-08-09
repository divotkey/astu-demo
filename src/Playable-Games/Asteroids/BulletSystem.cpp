/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#include "BulletSystem.h"
#include "CBullet.h"

using namespace astu;
using namespace std;

const EntityFamily BulletSystem::FAMILY = EntityFamily::Create<CBullet>();

BulletSystem::BulletSystem()
    : BaseService("Bullet System")
    , OneFamilyEntitySystem(FAMILY)    
{
    // Intentionally left empty.
}

void BulletSystem::OnStartup()
{
    // Intentionally left empty.
}

void BulletSystem::OnShutdown()
{
    // Intentionally left empty.
}

bool BulletSystem::OnCollision(astu::Entity& entityA, astu::Entity& entityB)
{
    if (entityA.HasComponent<CBullet>()) {
        GetEntityService().RemoveEntity(entityA);
    }
    if (entityB.HasComponent<CBullet>()) {
        GetEntityService().RemoveEntity(entityB);
    }
    return false;
}
