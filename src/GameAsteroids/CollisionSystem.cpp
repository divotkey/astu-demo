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
#include "CollisionSystem.h"

using namespace astu;
using namespace std;

const EntityFamily CollisionSystem::FAMILY = EntityFamily::Create<Collider, Pose2>();

CollisionSystem::CollisionSystem(int updatePriority)
    : Service("Collision System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void CollisionSystem::OnStartup()
{
    collisionEvents = ASTU_GET_SERVICE(SignalService<CollisionEvent>);
}

void CollisionSystem::OnShutdown()
{
    collisionEvents = nullptr;
}

void CollisionSystem::OnUpdate()
{
    auto & entities = GetEntityView();

    for (size_t j = 0; j < entities.size(); ++j) {
        auto & entityA = entities[j];
        auto & poseA = entityA->GetComponent<Pose2>();
        auto & collA = entityA->GetComponent<Collider>();

        for (size_t i = j + 1; i < entities.size(); ++i) {
            auto & entityB = entities[i];
            auto & poseB = entityB->GetComponent<Pose2>();
            auto & collB = entityB->GetComponent<Collider>();

            // Check collision categories and masks.
            if ( (collA.categoryBits & collB.collisionMask) 
                 && (collB.categoryBits & collA.collisionMask))
            {
                // Check for collision (interpenetration).
                if (IsColliding(poseA, collA, poseB, collB)) {
                    // Report collision
                    collisionEvents->FireSignal(CollisionEvent(entityA, entityB));
                }
            }

        }
    }
 }

bool CollisionSystem::IsColliding(Pose2 &poseA, Collider &colA, Pose2 &poseB, Collider &colB)
{
    auto delta = poseA.transform.GetTranslation() - poseB.transform.GetTranslation();
    return delta.LengthSquared() < (colA.radius + colB.radius) * (colA.radius + colB.radius);
}