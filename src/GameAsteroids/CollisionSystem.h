/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "Collider.h"

// AST Utilities includes
#include <ECS.h>
#include <Suite2D.h>

class CollisionEvent {
public:
    std::shared_ptr<astu::Entity> entityA;
    std::shared_ptr<astu::Entity> entityB;

    CollisionEvent(std::shared_ptr<astu::Entity> a, std::shared_ptr<astu::Entity>b)
        : entityA(a), entityB(b) {}
};

class CollisionSystem 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    CollisionSystem(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    /** Used to report collisions. */
    std::shared_ptr<astu::SignalService<CollisionEvent>> collisionEvents;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    


    bool IsColliding(astu2d::CPose &poseA, Collider &colA, astu2d::CPose &poseB, Collider &colB);
};