/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>

class CAsteroid : public astu::EntityComponent {
public: 
	/** The different type of asteroids we have. */
	enum class Type {Big, Medium, Small};

	/** The type of this asteroid. */
	Type type;

	/** The minimum velocity this asteroid can move. */
	float minVelocity;

	/** The maximum velocity this asteroid can move. */
	float maxVelocity;

	/**
	 * Constructor.
	 *  
	 * @param minVel	the minimum velocity this asteroid can move
	 * @param maxVel	the maximum velocity this asteroid can move
	 */
	CAsteroid(Type t, float minVel, float maxVel) 
		: type(t), minVelocity(minVel), maxVelocity(maxVel)
	{
		// Intentionally left empty.
	}

	// Inherited via EntityComponent
	virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<CAsteroid>(*this);
	}    
};