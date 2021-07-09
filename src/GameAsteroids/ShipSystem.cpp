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
#include <cmath>
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

    // Calc desired torque based on current user input.
    const float targetTorque = steerAxis->GetValue() * ship.maxTorque;

    // Calc difference (error) between current torque and user applied torque.
    const float e = targetTorque - ship.curTorque;

    // Determine velocity of torque change.
    float v = (e == 0.0) ? 0.0f : std::copysignf(ship.torqueSpeed, e);

    // Update and current torque.
    ship.curTorque += v * GetElapsedTimeF();

    // cout << "e = " << e << " | " << ship.curTorque << " | " << targetTorque << endl;

    // Apply current torque.
    body.ApplyTorque(ship.curTorque);

    // Apply current thrust.
    float curThrust = thrustAxis->GetValue() * ship.maxThrust;
    body.ApplyForce( body.GetWorldVector(0, -curThrust) );
}