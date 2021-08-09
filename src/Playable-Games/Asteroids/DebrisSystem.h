/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>
#include <AstuServices.h>
#include <AstuSuite2D.h>

class DebrisSystem 
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
	DebrisSystem(int updatePriority = astu::Priority::Normal);

private:
	// The family of entities this system processes
	static const astu::EntityFamily FAMILY;

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