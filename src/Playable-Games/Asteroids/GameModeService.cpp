/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "GameModeService.h"
#include "MeshData.h"
#include "Constants.h"

// AST-Utilities includes
#include <AstuMath.h>

#define LEFT_SIDE	0
#define RIGHT_SIDE	1
#define TOP_SIDE	2
#define BOTTOM_SIDE	3

using namespace astu2d;
using namespace astu;
using namespace std;

#define RANDOM_ELEM(a) a[Random::GetInstance().NextInt(0, static_cast<int>(a.size()))]

GameModeService::GameModeService()
	: BaseService("Game Mode Service")
{
	// Intentionally left empty.    
}

void GameModeService::OnStartup()
{
	// Configure camera.
	GetCamera().ShowFitting(WORLD_WIDTH, WORLD_HEIGHT);

	// Uncomment to visualize world boundaries
	// ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(PolylineBuilder()
	// 	.Color(RalColors::TrafficGreyB)
	// 	.VertexBuffer(ShapeGenerator().GenRectangle(WORLD_WIDTH, VIEW_HEIGHT))
	// 	.Build());

	// Start game.
	numAsteroidsAlive = 0;
	numAsteroidsToSpawn = 4;
	numLifes = 3;
	score = 0;

	EmitSignal(GameEvent::CreateLifeUpdate(numLifes));
	UpdateScore();

	SpawnAsteroids(numAsteroidsToSpawn);
	SpawnShip();
}

void GameModeService::OnShutdown()
{
	ASTU_SERVICE(EntityService).RemoveAll();
}

void GameModeService::SpawnAsteroids(int n)
{
	for (int i = 0; i < n; ++i) {
		SpawnAsteroid();
	}
}

void GameModeService::SpawnAsteroid()
{
	const auto& asteroidData = RANDOM_ELEM(kBigAsteroids);

	Vector2f spawnPoint;
	switch (Random::GetInstance().NextInt(0, 4)) {
	case LEFT_SIDE:
		spawnPoint.x = -WORLD_WIDTH / 2 - asteroidData.radius;
		spawnPoint.y = Random::GetInstance().NextFloat(-WORLD_HEIGHT / 2, WORLD_HEIGHT / 2);
		break;

	case RIGHT_SIDE:
		spawnPoint.x = WORLD_WIDTH / 2 + asteroidData.radius;
		spawnPoint.y = Random::GetInstance().NextFloat(-WORLD_HEIGHT / 2, WORLD_HEIGHT / 2);
		break;

	case BOTTOM_SIDE:
		spawnPoint.x = Random::GetInstance().NextFloat(-WORLD_WIDTH / 2, WORLD_WIDTH / 2);
		spawnPoint.y = WORLD_WIDTH / 2 - asteroidData.radius;
		break;

	case TOP_SIDE:
		spawnPoint.x = Random::GetInstance().NextFloat(-WORLD_WIDTH / 2, WORLD_WIDTH / 2);
		spawnPoint.y = -WORLD_WIDTH / 2 + asteroidData.radius;
		break;

	default:
		assert(false);
		break;
	}

	AddEntity(asteroidData.name, spawnPoint);
	++numAsteroidsAlive;
}

void GameModeService::SpawnMediumAsteroids(int n, const Vector2f& p)
{
	for (int i = 0; i < n; ++i) {
	const auto& asteroidData = RANDOM_ELEM(kMediumAsteroids);

		AddEntity(asteroidData.name, p);
		++numAsteroidsAlive;
	}
}

void GameModeService::SpawnSmallAsteroids(int n, const Vector2f& p)
{
	for (int i = 0; i < n; ++i) {
	const auto& asteroidData = RANDOM_ELEM(kSmallAsteroids);

		AddEntity(asteroidData.name, p);
		++numAsteroidsAlive;
	}
}

void GameModeService::SpawnShip()
{
	AddEntity("Ship", 0, 0);
}

void GameModeService::UpdateScore(int deltaScore)
{
	score += deltaScore;	
	EmitSignal(GameEvent::CreateScoreUpdate(score));

	if (score > 0 && score % EXTRA_LIFE == 0) {
		UpdateLife(1);
	}	
}

void GameModeService::UpdateLife(int deltaLife)
{
	numLifes += deltaLife;
	EmitSignal(GameEvent::CreateLifeUpdate(numLifes));
	if (deltaLife < 0 && numLifes > 0) {
		ASTU_SERVICE(TaskService).AddTask(DelegateTaskBuilder()
			.Delay(SHIP_SPAWN_DELAY)
			.Delegate([this](){ SpawnShip(); })
			.Build()
		);
	}
}


bool GameModeService::OnSignal(const GameEvent& signal)
{
	switch (signal.type) {

	case GameEvent::Type::BigAsteroidDestroyed:
		AddEntity("BigAsteroidDebris", signal.position);
		SpawnMediumAsteroids(ASTEROID_NUM_CHILDREN, signal.position);
		--numAsteroidsAlive;
		UpdateScore(BIG_ASTEROID_SCORE);
		break;

	case GameEvent::Type::MediumAsteroidDestroyed:
		AddEntity("MediumAsteroidDebris", signal.position);
		SpawnSmallAsteroids(ASTEROID_NUM_CHILDREN, signal.position);
		--numAsteroidsAlive;
		UpdateScore(MEDIUM_ASTEROID_SCORE);
		break;

	case GameEvent::Type::SmallAsteroidDestroyed:
		AddEntity("SmallAsteroidDebris", signal.position);
		--numAsteroidsAlive;

		UpdateScore(SMALL_ASTEROID_SCORE);
		if (numAsteroidsAlive <= 0) {
			SpawnAsteroids(numAsteroidsToSpawn += 2);
		}
		break;

	case GameEvent::Type::ShipDestroyed:
		AddEntity("ShipDebris", signal.position);
		UpdateLife(-1);
		break;
	}

	return false;
}
