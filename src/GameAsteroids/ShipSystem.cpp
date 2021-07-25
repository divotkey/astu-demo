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
    entityFactory = ASTU_GET_SERVICE(EntityFactoryService);
}

void ShipSystem::OnShutdown()
{
    entityFactory = nullptr;
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

    // Update thrust and steering input.
    ship.steeringInput.SetTargetValue(steerAxis->GetValue());
    ship.steeringInput.Update(GetElapsedTimeF());
    ship.thrustInput.SetTargetValue(thrustAxis->GetValue());
    ship.thrustInput.Update(GetElapsedTimeF());

    // Apply current torque.
    body.ApplyTorque(ship.steeringInput.GetCurrentValue() * ship.maxTorque);

    // Apply current thrust.
    float curThrust =  ship.thrustInput.GetCurrentValue() * ship.maxThrust;
    body.ApplyForce( body.GetWorldVector(0, -curThrust) );

    // Draw axes state for debugging purpose.
    DrawAxesState(ship.steeringInput, ship.thrustInput);
}

void ShipSystem::DrawAxesState(LinearInterpolator1f & hAxis, LinearInterpolator1f & vAxis)
{
    auto & wndSrv = ASTU_SERVICE(WindowService);
    const float ox = wndSrv.GetWidth() / 2.0f;
    const float oy = wndSrv.GetHeight() / 2.0f;
    const float w = 100.0f;
    const float h = 100.0f;

    SetDrawColor(WebColors::Black);
    DrawLine(ox + -w/2, oy + 0, ox + w/2, oy + 0);
    DrawLine(ox + 0, oy + -h/2, ox + 0, oy + h/2);

    float x = hAxis.GetTargetValue() * w / 2;
    float y = vAxis.GetTargetValue() * h / 2;

    SetDrawColor(WebColors::Yellow);
    DrawLine(ox + x, oy + -w * 0.1f, ox + x, oy + w * 0.1f);
    DrawLine(ox - w * 0.1f, oy + y, ox + w * 0.1f, oy + y);

    x = hAxis.GetCurrentValue() * w / 2;
    y = vAxis.GetCurrentValue() * h / 2;

    SetDrawColor(WebColors::Red);
    DrawLine(ox + x, oy + -w * 0.1f, ox + x, oy + w * 0.1f);
    DrawLine(ox - w * 0.1f, oy + y, ox + w * 0.1f, oy + y);
}