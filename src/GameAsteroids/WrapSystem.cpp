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
#include "Wrap.h"
#include "Body2.h"
#include "WrapSystem.h"

using namespace astu;
using namespace std;

const EntityFamily WrapSystem::FAMILY = EntityFamily::Create<Wrap, Body2>();

WrapSystem::WrapSystem(int updatePriority)
    : Service("Wrap System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void WrapSystem::SetWrapSize(float w, float h)
{
    upperLeft.Set(-w / 2, -h / 2);
    lowerRight.Set(w / 2, h / 2);
}

void WrapSystem::OnStartup()
{
    // Intentionally left empty.
}

void WrapSystem::OnShutdown()
{
    // Intentionally left empty.
}

void WrapSystem::OnUpdate()
{
    ProcessEntities();
}

void WrapSystem::ProcessEntity(Entity & entity)
{
    auto& body = entity.GetComponent<Body2>();
    if (body.GetLinearPosition().x < upperLeft.x) {
        body.SetLinearPosition(lowerRight.x, body.GetLinearPosition().y);
    } else if (body.GetLinearPosition().x > lowerRight.x) {
        body.SetLinearPosition(upperLeft.x, body.GetLinearPosition().y);
    }

    if (body.GetLinearPosition().y < upperLeft.y) {
        body.SetLinearPosition(body.GetLinearPosition().x, lowerRight.y);
    } else if (body.GetLinearPosition().y > lowerRight.y) {
        body.SetLinearPosition(body.GetLinearPosition().x, upperLeft.y);
    }
}

