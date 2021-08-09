/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>
#include <AstuInput.h>
#include <AstuServices.h>

class GunSystem 
	: public astu::BaseService
	, private astu::IteratingEntitySystem
	, private astu::TimeClient
	, private astu::EntityFactoryClient
{
public:

	/**
	 * Constructor.
	 * 
	 * @param updatePriority	the update priority of this system
	 */
	GunSystem(int updatePriority = astu::Priority::Normal);

private:
	// The family of entities this system processes
	static const astu::EntityFamily FAMILY;

	/** Used to fire guns. */
	std::shared_ptr<astu::ActionBinding> fireAction;

	/** Whether the trigger has been pulled. */
	bool trigger;

	// Inherited via BaseService
	virtual void OnStartup() override;
	virtual void OnShutdown() override;

	// Inherited via IteratingEntitySystem
	virtual void ProcessEntity(astu::Entity& entity) override;
};