/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "Body2.h"
#include "PhysicsSystem.h"

// AST Utilities includes
#include <Suite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily PhysicsSystem::FAMILY = EntityFamily::Create<CPose, Body2>();

PhysicsSystem::PhysicsSystem(int updatePriority)
    : BaseService("Physics System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
    , EntityListener(FAMILY)
{
    // Intentionally left empty.
}

void PhysicsSystem::OnUpdate()
{
    UpdateBodies( static_cast<float>(GetElapsedTime()) );
    ClearForces();
    UpdateTransforms();
}

void PhysicsSystem::OnEntityAdded(shared_ptr<Entity> entity)
{
    auto &pose = entity->GetComponent<CPose>();
    auto &body = entity->GetComponent<Body2>();

    // Copy initial position and orientation to physics body.
    body.RestoreFromTransform(pose.transform);
}

void PhysicsSystem::OnEntityRemoved(shared_ptr<Entity> entity)
{
    // Intentionally left empty.
}

void PhysicsSystem::UpdateBodies(float dt)
{
    for (auto entity : GetEntityView()) {
        entity->GetComponent<Body2>().Step(dt);
    }
}

void PhysicsSystem::ClearForces()
{
    for (auto entity : GetEntityView()) {
        entity->GetComponent<Body2>().ClearForces();
    }
}

void PhysicsSystem::UpdateTransforms()
{
    for (auto entity : GetEntityView()) {
        auto &pose = entity->GetComponent<CPose>();
        auto &body = entity->GetComponent<Body2>();
        body.StoreToTransform(pose.transform);
    }
}

