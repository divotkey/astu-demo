/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <Services.h>
#include <ECS.h>

class PhysicsSystem 
    : public astu::BaseService
    , private astu::Updatable
    , private astu::OneFamilyEntitySystem
    , private astu::EntityListener
    , private astu::TimeClient
{
public:

    /**
     * Constructor.
     */
    PhysicsSystem(int updatePriority = astu::Priority::Normal);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    void UpdateBodies(float dt);
    void ClearForces();
    void UpdateTransforms();

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via EntityListener
    virtual void OnEntityAdded(std::shared_ptr<astu::Entity> entity) override;
    virtual void OnEntityRemoved(std::shared_ptr<astu::Entity> entity) override;

};