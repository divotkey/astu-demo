/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// C++ Standard Library includes
#include <algorithm>
#include <iostream>

// AST Utilities includes 
#include <Keyboard.h>
#include <EntityFactoryService.h>

// Local includes
#include "Ship.h"
#include "Gun.h"
#include "Pose2.h"
#include "Body2.h"
#include "GunSystem.h"

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
    fireAction = ASTU_SERVICE(InputMapperService)
        .BindAction("Fire");
}

void GunSystem::OnShutdown()
{
    ASTU_SERVICE(InputMapperService).RemoveActionBinding(fireAction);
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

    // if (body.GetLinearPosition().y < upperLeft.y) {
    //     body.SetLinearPosition(body.GetLinearPosition().x, lowerRight.y);
    // } else if (body.GetLinearPosition().y > lowerRight.y) {
    //     body.SetLinearPosition(body.GetLinearPosition().x, upperLeft.y);
    // }
}

bool GunSystem::IsFirePressed(int ctrl) const
{
    // This dummy functions does not realy use a game controller
    // and ignors the controller index as well.

    return Keyboard().IsPressed(Keyboard::KEY_SPACE);
}

