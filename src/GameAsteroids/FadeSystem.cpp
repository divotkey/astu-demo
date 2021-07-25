/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "FadeSystem.h"
#include "Fadable.h"

// AST-Utilities includes
#include <Suite2D.h>

// C++ Standard Library includes
#include <algorithm>
#include <iostream>

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily FadeSystem::FAMILY 
    = EntityFamily::Create<Fadable, CScene>();

FadeSystem::FadeSystem(int updatePriority)
    : Service("Fade System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
{
    // Intentionally left empty
}

void FadeSystem::OnStartup()
{
    // Intentinoally left empty.
}

void FadeSystem::OnShutdown()
{
    // Intentinoally left empty.
}

void FadeSystem::OnUpdate()
{
    ProcessEntities();
}

void FadeSystem::ProcessEntity(Entity & entity)
{
    auto &fadeable = entity.GetComponent<Fadable>();
    auto &scene = entity.GetComponent<CScene>();

    fadeable.elapsed += GetElapsedTimeF();
    float a = min(1.0f, fadeable.elapsed / fadeable.duration);
    assert(a >= 0 && a <= 1);
    scene.spatial->SetTransparance(1.0f - a);

    if (fadeable.elapsed >= fadeable.duration) {
        GetEntityService().RemoveEntity(entity);
    }
}