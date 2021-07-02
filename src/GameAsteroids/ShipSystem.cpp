/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "ShipSystem.h"
#include "Ship.h"
#include "Body2.h"

// C++ Standard Library includes
#include <algorithm>
#include <iostream> // just for debugging


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
    thrustAxis = ASTU_SERVICE(InputMappingService).BindAxis("Thrust");
    steerAxis = ASTU_SERVICE(InputMappingService).BindAxis("Steer");
}

void ShipSystem::OnShutdown()
{
    ASTU_SERVICE(InputMappingService).RemoveAxisBinding(thrustAxis);
    ASTU_SERVICE(InputMappingService).RemoveAxisBinding(steerAxis);
}

void ShipSystem::OnUpdate()
{
    ProcessEntities();
}

void ShipSystem::ProcessEntity(Entity & entity)
{
    auto& body = entity.GetComponent<Body2>();
    auto& ship = entity.GetComponent<Ship>();


    body.ApplyTorque(ship.torque * steerAxis->GetValue());

    // float curThrust = std::max(0.0f, thrustAxis->GetValue() * ship.thrust);
    float curThrust = thrustAxis->GetValue() * ship.thrust;
    body.ApplyForce( body.GetWorldVector(0, -curThrust) );
}