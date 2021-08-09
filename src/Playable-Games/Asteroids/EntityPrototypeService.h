/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes
#include "MeshData.h"
#include "CAsteroid.h"

// AST-Utilities includes
#include <AstuServices.h>
#include <AstuECS.h>

class EntityPrototypeService : public astu::BaseService
{
public:

	  // Constructor.
	  EntityPrototypeService(bool debug = false);

private:
	  // Whether debug mode is activated.
	  bool debug;

	  // Inherited via BaseService
	  virtual void OnStartup() override;
	  virtual void OnShutdown() override;

	  using Vertices = std::vector<astu::Vector2f>;

	  std::shared_ptr<astu::Entity> CreateBoundary(float w, float h);
	  std::shared_ptr<astu::Entity> CreateShip();
	  std::shared_ptr<astu::Entity> CreateBullet();
	  std::shared_ptr<astu::Entity> CreateDebris(const astu::Color4f& c, float radius);
	  std::shared_ptr<astu::Entity> CreateShipDebris();
	  std::shared_ptr<astu::Entity> CreateAsteroid(const MeshData& mesh, CAsteroid::Type type);
};