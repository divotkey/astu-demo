/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "GunSystem.h"
#include "Ship.h"
#include "Gun.h"
#include "Pose2.h"
#include "Body2.h"

// AST Utilities includes 
#include <EntityFactoryService.h>

// C++ Standard Library includes
#include <algorithm>
#include <iostream>

using namespace astu;
using namespace std;

const EntityFamily GunSystem::FAMILY 
    = EntityFamily::Create<Pose2, Body2, Gun, Ship>();

GunSystem::GunSystem(int updatePriority)
    : Service("Gun System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void GunSystem::OnStartup()
{
    fireAction = ASTU_SERVICE(InputMappingService)
        .BindAction("Fire");
}

void GunSystem::OnShutdown()
{
    ASTU_SERVICE(InputMappingService).RemoveActionBinding(fireAction);
}

void GunSystem::OnUpdate()
{
    ProcessEntities();
}

void GunSystem::ProcessEntity(Entity & entity)
{
    auto & gun = entity.GetComponent<Gun>();
    if (gun.cooldown > 0) {
        gun.cooldown = std::max(0.0f, gun.cooldown - GetElapsedTimeF());
    }

    auto & ship = entity.GetComponent<Ship>();
    if (gun.cooldown == 0 && fireAction->IsPressed()) {
        // Fire bullet.
        ++gun.bulletsFired;

        auto & pose = entity.GetComponent<Pose2>();

        auto bullet = ASTU_SERVICE(EntityFactoryService).CreateEntity("Bullet");
        auto & bulletBody = bullet->GetComponent<Body2>();
        auto & bulletPose = bullet->GetComponent<Pose2>();

        // bulletPose.transform.SetTranslation(body.GetWorldPoint(gun.offset));
        bulletPose.transform.SetTranslation(
            pose.transform.TransformPoint(gun.offset)
        );

        bulletPose.transform.SetRotation(
            pose.transform.GetRotation()
        );

        bulletBody.SetLinearVelocity(
            pose.transform.TransformVector(gun.direction * gun.muzzleVelocity)
        );

        GetEntityService().AddEntity(bullet);

        // Update cooldown.
        gun.cooldown = 1.0f / gun.roundsPerSecond;
    }
}