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
#include "Ship.h"
#include "Body2.h"
#include "ShipSystem.h"

using namespace astu;
using namespace std;

const EntityFamily ShipSystem::FAMILY = EntityFamily::Create<Ship, Body2>();

ShipSystem::ShipSystem(int updatePriority)
    : Service("Ship System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void ShipSystem::OnStartup()
{
    // Intentionally left empty.
}

void ShipSystem::OnShutdown()
{
    // Intentionally left empty.
}

void ShipSystem::OnUpdate()
{
    ProcessEntities();
}

void ShipSystem::ProcessEntity(Entity & entity)
{
    auto& body = entity.GetComponent<Body2>();
    auto& ship = entity.GetComponent<Ship>();

    body.ApplyTorque(ship.torque * GetAxis(ship.playerId, 0));

    body.ApplyForce(body.GetWorldVector(0, GetAxis(ship.playerId, 1) * ship.thrust));

    // mesh.spatial->SetLocalTransform(pose.transform);
}

float ShipSystem::GetAxis(int ctrl, int axis)
{
    // This dummy functions does not really use a game controller
    // and ignores the controller index as well.

    Keyboard kb;
    switch (axis) {
    case 0:
        if (kb.IsPressed(Keyboard::KEY_LEFT)) {
            return -1.0f;
        }
        if (kb.IsPressed(Keyboard::KEY_RIGHT)) {
            return 1.0f;
        }
        return 0;

    case 1:
        if (kb.IsPressed(Keyboard::KEY_UP)) {
            return -1.0f;
        }
        if (kb.IsPressed(Keyboard::KEY_DOWN)) {
            return 1.0f;
        }
        return 0;

    default:
        return 0;
    }

}
