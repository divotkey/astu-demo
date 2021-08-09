/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "GameEvent.h"

// AST-Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>

// C++ Standard Library includes
#include <string>
#include <array>
#include <vector>

class GameModeService 
	: public astu::BaseService
	, private astu2d::CameraClient
	, private astu::EntityFactoryClient
	, private astu::SignalListener<GameEvent>
	, private astu::SignalEmitter<GameEvent>
{
public:
		
	/**
	 * Constructor.
	 */
	GameModeService();

private:
	/** The number of asteroids that currently exists. */
	int numAsteroidsAlive;

	/** The number of new asteroids to spawn at the start of the level. */
	int numAsteroidsToSpawn;
	
	/** The number of lifes of the player. */
	int numLifes;

	/** The score of the player. */
	int score;

	/**
	 * Spawns asteroids.
	 * 
	 * @param n	the number of asteroids to spawn
	 */
	void SpawnAsteroids(int n);

	/**
	 * Spawns one asteroid.
	 */
	void SpawnAsteroid();

	/**
	 * Spawns medium size asteroids.
	 * 
	 * @param n	the number of asteroids to spawn
	 * @param p	the spawn point of the asteroids
	 */
	void SpawnMediumAsteroids(int n, const astu::Vector2f& p);

	/**
	 * Spawns small size asteroids.
	 * 
	 * @param n	the number of asteroids to spawn
	 * @param p	the spawn point of the asteroids
	 */
	void SpawnSmallAsteroids(int n, const astu::Vector2f& p);

	/**
	 * Spawns a new player ship entity.
	 */
	void SpawnShip();

	/**
	 * Updates the player's score.
	 * 
	 * @param deltaScore the additional score points
	 */
	void UpdateScore(int deltaScore = 0);

	/**
	 * Updates the player's number of life.
	 * 
	 * @param deltaLife	the difference to the current number of lifes
	 */
	void UpdateLife(int deltaLife = 0);

	// Inherited via BaseService
	virtual void OnStartup() override;
	virtual void OnShutdown() override;

	// Inherited via private astu::SignalListener<GameEvent>
	virtual bool OnSignal(const GameEvent & signal) override;
};
