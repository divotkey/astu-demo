/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "ParticleSystem.h"
#include "CThruster.h"

// AST Utilities includes
#include <AstuECS.h>
#include <AstuServices.h>
#include <AstuSuite2D.h>

/**
 * Uses particle systems to visualize thrust of ship entities.
 */
class ThrusterSystem 
	: public astu::BaseService
	, private astu::IteratingEntitySystem
	, private astu::TimeClient
	, private astu::EntityListener
	, private astu2d::LineRendererClient2f
	, private astu2d::CameraClient
{
public:

	/**
	 * Constructor.
	 * 
	 * @param updatePriority	the update priority of this system
	 */
	ThrusterSystem(int updatePriority = astu::Priority::Normal);

private:
	// The family of entities this system processes
	static const astu::EntityFamily FAMILY;

	/**
	 * Combines a particle system and a color.
	 * 
	 * This struct is used to render particle system with alive particles
	 * of entities, which have already been destroyed.
	 */
	struct CoolDown {
		std::unique_ptr<ParticleSystem> particleSystem;
		astu::Color4f color;

		CoolDown(std::unique_ptr<ParticleSystem> ps, const astu::Color4f& c)
			: particleSystem(std::move(ps)), color(c) {}
	};

	/** Particles which must cool down before beeing freed. */
	std::vector<CoolDown> cooldowns;

	/**
	 * Updates cooldown particle systems.
	 */
	void UpdateCooldown();

	/**
	 * Emits new particles representing fragments.
	 * 
	 * @param rate		the emmision rate, used calc the number of particles
	 * @param thruster	the thruster containing particle parameters
	 * @param pose		the pose of the entites used to intialize particles
	 */
	void EmitFragments(float rate, CThruster& thruster, const astu2d::CPose& pose);

	/**
	 * Renders a thrust fragment.
	 * 
	 * @param ps	contains the particles describing the fragments positions
	 * @param c		the color used to render the particles
	 */
	void RenderFragments(ParticleSystem& ps, const astu::Color4f& c);

	// Inherited via BaseService
	virtual void OnStartup() override;
	virtual void OnShutdown() override;

	// Inherited via IteratingEntitySystem
	virtual void OnUpdate() override;
	virtual void ProcessEntity(astu::Entity& entity) override;

	// Inherited via EntityListener
	virtual void OnEntityAdded(std::shared_ptr<astu::Entity> entity) override;
	virtual void OnEntityRemoved(std::shared_ptr<astu::Entity> entity) override;
};