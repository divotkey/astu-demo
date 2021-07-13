/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// C++ Standard Library includes
#include <iostream>

// Local includes
#include "Pose2.h"
#include "Mesh2.h"
#include "Mesh2System.h"

using namespace astu;
using namespace std;

const EntityFamily Mesh2System::FAMILY = EntityFamily::Create<Pose2, Mesh2>();

Mesh2System::Mesh2System(int updatePriority)
    : Service("Mesh2 Entity System")
    , Updatable(updatePriority)
    , OneFamilyEntitySystem(FAMILY)
    , EntityListener(FAMILY)
{
    // Intentionally left empty
}

void Mesh2System::OnStartup()
{
    root = ASTU_SERVICE(SceneGraph2D).GetRoot();
}

void Mesh2System::OnShutdown()
{
    root = nullptr;
}

void Mesh2System::OnUpdate()
{
    ProcessEntities();
}

void Mesh2System::ProcessEntity(Entity & entity)
{
    auto& pose = entity.GetComponent<Pose2>();
    auto& mesh = entity.GetComponent<Mesh2>();

    mesh.spatial->SetLocalTransform(pose.transform);
}

void Mesh2System::OnEntityAdded(std::shared_ptr<astu::Entity> entity)
{
    auto& pose = entity->GetComponent<Pose2>();
    auto& mesh = entity->GetComponent<Mesh2>();

    mesh.spatial->SetLocalTransform(pose.transform);
    root->AttachChild(mesh.spatial);
}

void Mesh2System::OnEntityRemoved(std::shared_ptr<astu::Entity> entity)
{
    auto& mesh = entity->GetComponent<Mesh2>();
    root->DetachChild(mesh.spatial);
}