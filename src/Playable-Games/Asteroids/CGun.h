/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>
#include <AstuMath.h>

class CGun : public astu::EntityComponent {
public: 
	/** The number of bullets per second. */
	float fireRate;

	/** The remaining time until the gun is ready to fire. */
	float cooldown;

	/** The initial velocity of projectiles this gun fires. */
	float muzzleVelocity;

	/** The determines the spawn point of projectiles in local space. */
	astu::Vector2f mountPoint;

	/** The direction the gun fires projectiles in local space. */
	astu::Vector2f direction;

	/**
	 * Constructor.
	 * 
	 * @param rate	the fire rate in bullets per seconds
	 * @param speed	the muzzle velocity of bullets
	 * @param pos	the mount point of the gun in local space
	 * @param dir	the diredction of the gun in local space
	 */
	CGun(float rate, float speed, const astu::Vector2f& pos, const astu::Vector2f& dir) 
		: fireRate(rate)
		, cooldown(0)
		, muzzleVelocity(speed)
		, mountPoint(pos)
		, direction(dir)
	{
		// Intentionally left empty.
	}

	// Inherited via EntityComponent
	virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<CGun>(*this);
	}    
};