/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>

class CShip : public astu::EntityComponent {
public: 
	/** The maximum torque the player can use to steer the ship. */
	float maxTorque;

	/** The maximum thrust the player can use to accelerate the ship. */
	float maxThrust;

	/** Describes the amount of currently active thrust. */
	float curThrust;

	/**
	 * Constructor.
	 * 
	 * @param maxTorque	the maximum torque
	 */
	CShip(float maxThrust, float maxTorque) 
		: maxThrust(maxThrust)
		, maxTorque(maxTorque)
		, curThrust(0)
	{
		// Intentionally left empty.
	}

	// Inherited via EntityComponent
	virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<CShip>(*this);
	}    
};