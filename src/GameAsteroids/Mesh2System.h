/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <UpdateService.h>
#include <EntitySystems.h>
#include <Scene2D.h>

class Mesh2System 
    : public astu::Updatable
    , private astu::OneFamilyEntitySystem
    , private astu::EntityListener
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority    the priority used to update this system
     */
    Mesh2System(int updatePriority = 0);

private:
    /** The entity family this system processes. */
    static const astu::EntityFamily FAMILY;

    // Inherited via Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;    

    // Inherited via OneFamilyEntitySystem
    virtual void ProcessEntity(astu::Entity & entity) override;

    // Inherited via EntityListener
    virtual void OnEntityAdded(std::shared_ptr<astu::Entity> entity) override;
    virtual void OnEntityRemoved(std::shared_ptr<astu::Entity> entity) override;

    /** The root node where to attach the entities. */
    std::shared_ptr<astu::Node2D> root;
};