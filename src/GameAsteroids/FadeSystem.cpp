/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "FadeSystem.h"
#include "Fadable.h"
#include "Mesh2.h"

// AST Utilities includes 
#include <EntityFactoryService.h>

// C++ Standard Library includes
#include <algorithm>
#include <iostream>

using namespace astu;
using namespace std;

const EntityFamily FadeSystem::FAMILY 
    = EntityFamily::Create<Fadable, Mesh2>();

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
    auto &mesh = entity.GetComponent<Mesh2>();

    fadeable.elapsed += GetElapsedTimeF();
    float a = min(1.0f, fadeable.elapsed / fadeable.duration);
    assert(a >= 0 && a <= 1);
    mesh.spatial->SetTransparance(1.0f - a);

    if (fadeable.elapsed >= fadeable.duration) {
        GetEntityService().RemoveEntity(entity);
    }
}