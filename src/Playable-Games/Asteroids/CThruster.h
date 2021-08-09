/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "ParticleSystem.h"

// AST Utilities includes
#include <AstuGraphics.h>
#include <AstuECS.h>

class CThruster : public astu::EntityComponent {
public: 
	/** The number of fragments. */
	unsigned int numFragments;

	/** The time to live. */
	float ttl;

	/** The initial radius of the fragments. */
	float radius;

	/** The offset of the fragment emmision. */
	astu::Vector2f offset;

	/** The fragment color. */
	astu::Color4f color;


	/** Used to remember to fractional part of fragments to emit. */
	float emitFraction;

	/** The particle system used to visualize thrust. */
	std::unique_ptr<ParticleSystem> particleSystem;

	/**
	 * Constructor.
	 * 
	 * @param n		the number of fragments
	 * @param ttl	the time to life for fragments in seconds
	 * @param c		the fragment color
	 * @param r		the initial radius of the fragments
	 * @param o		the offset of the fragment emmision
	 */
	CThruster(unsigned int n, float ttl, const astu::Color4f c, float r, const astu::Vector2f& o) 
		: numFragments(n)
		, ttl(ttl)
		, radius(r)
		, offset(o)
		, color(c)
		, emitFraction(0.0f)		
	{
		// Intentionally left empty.
	}

	/**
	 * Copy-constructor required because of unique_ptr member.
	 * 
	 * @param other	the other instance to copy
	 */
	CThruster(const CThruster& other)
		: numFragments(other.numFragments)
		, ttl(other.ttl)
		, radius(other.radius)
		, offset(other.offset)
		, color(other.color)
	{
		// Intentionally left empty.
	}

	// Inherited via EntityComponent
	virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<CThruster>(*this);
	}    
};