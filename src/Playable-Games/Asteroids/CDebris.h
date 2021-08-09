/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "ParticleSystem.h"

// AST Utilities includes
#include <AstuECS.h>
#include <AstuMath.h>

// C++ Standard Library includes
#include <memory>

class CDebris : public astu::EntityComponent {
public: 
	/** The particle system of this debris. */
	std::unique_ptr<ParticleSystem> particleSystem;

	/** The number of fragments. */
	unsigned int numFragments;

	/** The time to live. */
	float ttl;

	/** The initial radius of the debris fragments. */
	float radius;

	/** The debris color. */
	astu::Color4f color;

	/** Whether this is ship debris. */
	bool ship;

	/**
	 * Constructor.
	 * 
	 * @param n		the number of debris fragments
	 * @param ttl	the time to life for fragments in seconds
	 * @param c		the debris color
	 * @param r		the initial radius of the fragments
	 * @param ship	indicates ship debris
	 */
	CDebris(unsigned int n, float ttl, const astu::Color4f c, float r, bool ship = false) 
		: numFragments(n)
		, ttl(ttl)
		, radius(r)
		, color(c)
		, ship(ship)
	{
		// Intentionally left empty.
	}

	/**
	 * Copy-constructor required because of unique_ptr member.
	 * 
	 * @param other	the other instance to copy
	 */
	CDebris(const CDebris& other)
		: numFragments(other.numFragments)
		, ttl(other.ttl)
		, radius(other.radius)
		, color(other.color)
		, ship(other.ship)
	{
		// Intentionally left empty.
	}

	// Inherited via EntityComponent
	virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<CDebris>(*this);
	}    
};