/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */


#pragma once

// AST Utilities includes
#include <AstuECS.h>
#include <AstuSuite2D.h>

class BulletSystem 
    : public astu::BaseService
    , private astu::OneFamilyEntitySystem
    , private astu2d::CollisionListener
{
public:

    /** Constructor. */
    BulletSystem();

private:
    // The family of entities this system processes
    static const astu::EntityFamily FAMILY;

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via CollisionListener
    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;
};