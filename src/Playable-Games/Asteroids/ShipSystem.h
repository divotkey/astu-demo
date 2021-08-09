/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "GameEvent.h"

// AST Utilities includes
#include <AstuECS.h>
#include <AstuSuite2D.h>
#include <AstuInput.h>

class ShipSystem 
	: public astu::BaseService
	, private astu::IteratingEntitySystem
	, private astu2d::CollisionListener
    , private astu::SignalEmitter<GameEvent>
{
public:

	/**
	 * Constructor.
	 * 
	 * @param updatePriority	the update priority of this system
	 */
	ShipSystem(int updatePriority = astu::Priority::Normal);

private:
	// The family of entities this system processes
	static const astu::EntityFamily FAMILY;

	/** Used to accelerate the ship. */
	std::shared_ptr<astu::AxisBinding> thrustAxis;

	/** Used to steer the ship. */
	std::shared_ptr<astu::AxisBinding> turnAxis;

    /**
     * Destroys the ship entity.
     * 
     * @param entity	the ship entity
     */
    void DestroyShip(astu::Entity& entity);

	// Inherited via BaseService
	virtual void OnStartup() override;
	virtual void OnShutdown() override;

	// Inherited via IteratingEntitySystem
	virtual void ProcessEntity(astu::Entity& entity) override;

    // Inherited via CollisionListener
    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;
};