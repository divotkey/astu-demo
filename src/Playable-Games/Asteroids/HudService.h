/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "TextRenderService.h"
#include "GameEvent.h"

// AST Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>

class HudService 
	: public astu::BaseService
	, private astu::SignalListener<GameEvent>
	, private astu::Updatable
	, private astu2d::CameraClient
	, private astu2d::LineRendererClient2f
	, private astu::TimeClient
{
public:

	/**
	 * Constructor.
	 * 
	 * @param updatePriority	the priority to update this service
	 */
	HudService(int updatePriority = astu::Priority::Normal);

private:
	/** The current number of lifes. */
	int numLifes;

	/** The current score. */
	int score;

	/** Sum of delta times, used for FPS gauge. */
	double dtSum;

	/** Frames per second. */
	double fps;

	/** Number of delta times, used for FPS gauge. */
	int dtCnt;

	/** Used to render HUD elements. */
	std::shared_ptr<TextRenderService> textRenderer;

	// Inherited via BaseService
	virtual void OnStartup() override;
	virtual void OnShutdown() override;

	// Inherited via private astu::SignalListener<GameEvent>
	virtual bool OnSignal(const GameEvent & signal) override;

    // Inherited via Updatable
    virtual void OnUpdate() override;
};