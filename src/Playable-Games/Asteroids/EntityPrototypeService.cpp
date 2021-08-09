/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "EntityPrototypeService.h"
#include "Constants.h"
#include "MeshData.h"
#include "CShip.h"
#include "CGun.h"
#include "CBullet.h"
#include "CWrap.h"
#include "CDebris.h"
#include "CThruster.h"

// AST-Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

#define ASTEROID_CATEGORY	0x0001
#define SHIP_CATEGORY		0x0002
#define BULLET_CATEGORY		0x0004
#define BOUNDARY_CATEGORY	0x0008

EntityPrototypeService::EntityPrototypeService(bool debug)
	: BaseService("Entity Prototype Service")
	, debug(debug)
{
	// Intentionally left empty.    
}

void EntityPrototypeService::OnStartup()
{
	// Create and register entity prototypes.
	auto &entityFactory = ASTU_SERVICE(EntityFactoryService);

	// Register boundary entity prototypes.
	entityFactory.RegisterPrototype("HBoundary", CreateBoundary(WORLD_WIDTH, BOUNDARY_THICKNESS));
	entityFactory.RegisterPrototype("VBoundary", CreateBoundary(BOUNDARY_THICKNESS, WORLD_HEIGHT));

	// Register entity prototypes.
	entityFactory.RegisterPrototype("Ship", CreateShip());
	entityFactory.RegisterPrototype("Bullet", CreateBullet());
	entityFactory.RegisterPrototype("BigAsteroidDebris", CreateDebris(DEBRIS_COLOR, kBigAsteroids[0].radius));
	entityFactory.RegisterPrototype("MediumAsteroidDebris", CreateDebris(DEBRIS_COLOR, kMediumAsteroids[0].radius));
	entityFactory.RegisterPrototype("SmallAsteroidDebris", CreateDebris(DEBRIS_COLOR, kSmallAsteroids[0].radius));
	entityFactory.RegisterPrototype("ShipDebris", CreateShipDebris());

	// Register asteroids entities prototypes.
	for (int i = 0; i < kBigAsteroids.size(); ++i) {
		const auto& asteroidData = kBigAsteroids[i];
		entityFactory.RegisterPrototype(
			asteroidData.name, 
			CreateAsteroid(asteroidData, CAsteroid::Type::Big)
		);
	}

	for (int i = 0; i < kMediumAsteroids.size(); ++i) {
		const auto& asteroidData = kMediumAsteroids[i];
		entityFactory.RegisterPrototype(
			asteroidData.name, 
			CreateAsteroid(asteroidData, CAsteroid::Type::Medium)
		);
	}

	for (int i = 0; i < kSmallAsteroids.size(); ++i) {
		const auto& asteroidData = kSmallAsteroids[i];
		entityFactory.RegisterPrototype(
			asteroidData.name, 
			CreateAsteroid(asteroidData, CAsteroid::Type::Small)
		);
	}
}

void EntityPrototypeService::OnShutdown()
{
	  // Cleanup.
	  ASTU_SERVICE(EntityFactoryService).DeregisterAllPrototypes();
}

shared_ptr<Entity> EntityPrototypeService::CreateBoundary(float w, float h)
{
	  auto entity = make_shared<Entity>();
	  entity->AddComponent(make_shared<CPose>());

	  if (debug) {
	      entity->AddComponent(make_shared<CScene>(PolylineBuilder()
	          .Color(BOUNDARY_COLOR)
	          .VertexBuffer(ShapeGenerator().PolylineMode().GenRectangle(w, h))
	          .Build()));
	  }

	  entity->AddComponent(CBodyBuilder()
	      .Type(CBody::Type::Static)
	      .Build());

	  entity->AddComponent(CPolygonColliderBuilder()
	      .Polygon(ShapeGenerator().GenRectangle(w, h))
	      .Friction(0)
	      .Restitution(1)
		  .CategoryBits(BOUNDARY_CATEGORY)
		  .MaskBits(0xFFFF)
	      .Build());

	  return entity;
}

std::shared_ptr<astu::Entity> EntityPrototypeService::CreateShip()
{
	auto entity = make_shared<Entity>();

	entity->AddComponent(make_shared<CShip>(SHIP_MAX_THRUST, SHIP_MAX_TORQUE));
	entity->AddComponent(make_shared<CThruster>(
		SHIP_THRUST_NUM_FRAGMENTS, 
		SHIP_THRUST_TTL, 
		SHIP_THRUST_COLOR, 
		SHIP_THRUST_SPAWN_RADIUS,
		SHIP_THRUST_OFFSET
		));

	entity->AddComponent(make_shared<CGun>(
		GUN_FIRERATE, 
		GUN_MUZZLE_VELOCITY, 
		GUN_MOUNT_POINT, 
		GUN_DIRECTION)
		);

	entity->AddComponent(make_shared<CWrap>(
		WORLD_WIDTH + kShip.radius * 2,
		WORLD_HEIGHT + kShip.radius * 2)
	);

	entity->AddComponent(make_shared<CPose>());

	entity->AddComponent(make_shared<CScene>(NodeBuilder()
		.AttachChild(PolylineBuilder()
			.Color(SHIP_COLOR)
			.VertexBuffer(kShip.vertices)
			.Build())
		.Build())
	);

	if (debug) {
		// Add visual to show collider shape.
		auto node = dynamic_pointer_cast<Node>(entity->GetComponent<CScene>().spatial);
		node->AttachChild(PolylineBuilder()
			.Color(COLLIDER_COLOR)
			.VertexBuffer(kShipCollider.vertices)
			.Build());
		node->AttachChild(PolylineBuilder()
			.Color(COLLIDER_COLOR)
			.VertexBuffer(ShapeGenerator().GenCircle(kShipCollider.radius))
			.Build());
	}

	entity->AddComponent(CBodyBuilder()
		.Type(CBody::Type::Dynamic)
		.LinearDamping(SHIP_LINEAR_DAMPING)
		.AngularDamping(SHIP_ANGULAR_DAMPING)
		.Build()
	);

	entity->AddComponent(CPolygonColliderBuilder()
		.Polygon(kShipCollider.vertices)
		.Friction(0)
		.Restitution(1)
		.CategoryBits(SHIP_CATEGORY)
		.MaskBits(ASTEROID_CATEGORY | BOUNDARY_CATEGORY)
		.Build()
	);

	return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateAsteroid(const MeshData& mesh, CAsteroid::Type type)
{
	auto entity = make_shared<Entity>();
	entity->AddComponent(make_shared<CAsteroid>(type, ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY));
	entity->AddComponent(make_shared<CPose>());

	entity->AddComponent(make_shared<CWrap>(
		WORLD_WIDTH + mesh.radius * 2,
		WORLD_HEIGHT + mesh.radius * 2)
	);

	entity->AddComponent(make_shared<CScene>(NodeBuilder()
		.AttachChild(PolylineBuilder()
			.Color(ASTEROID_COLOR)
			.VertexBuffer(mesh.vertices)
			.Build())
		.Build())
	);

	if (debug) {
		// Add visual to show collider shape.
		auto node = dynamic_pointer_cast<Node>(entity->GetComponent<CScene>().spatial);
		node->AttachChild(PolylineBuilder()
			.Color(COLLIDER_COLOR)
			.VertexBuffer(ShapeGenerator().GenCircle(mesh.radius))
			.Build());
	}

	entity->AddComponent(CBodyBuilder()
		.Type(CBody::Type::Dynamic)
		.LinearDamping(0)
		.AngularDamping(0)
		.Build()
	);

	entity->AddComponent(CCircleColliderBuilder()
		.Radius(mesh.radius)
		.Friction(0)
		.Restitution(1)
		.CategoryBits(ASTEROID_CATEGORY)
		.MaskBits(SHIP_CATEGORY | BULLET_CATEGORY | BOUNDARY_CATEGORY)
		.Build()
	);

	return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateBullet()
{
	auto entity = make_shared<Entity>();
	entity->AddComponent(make_shared<CBullet>());

	if (BULLETS_DO_WARP) {
		entity->AddComponent(make_shared<CWrap>(
			WORLD_WIDTH + BULLET_RADIUS * 2,
			WORLD_HEIGHT + BULLET_RADIUS * 2)
		);
	}

	entity->AddComponent(make_shared<CAutoDestruct>(BULLET_LIFETIME));

	entity->AddComponent(make_shared<CPose>());

	entity->AddComponent(make_shared<CScene>(NodeBuilder()
		.AttachChild(PolylineBuilder()
			.Color(BULLET_COLOR)
			.VertexBuffer(ShapeGenerator().GenCircle(BULLET_RADIUS))
			.Build())
		.Build())
	);

	entity->AddComponent(CBodyBuilder()
		.Type(CBody::Type::Dynamic)
		.LinearDamping(0)
		.AngularDamping(0)
		.Build()
	);

	entity->AddComponent(CCircleColliderBuilder()
		.Radius(BULLET_RADIUS)
		.Friction(0)
		.Restitution(1)
		.CategoryBits(BULLET_CATEGORY)
		.MaskBits(ASTEROID_CATEGORY | BOUNDARY_CATEGORY)
		.Build()
	);

	return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateDebris(const astu::Color4f& c, float radius)
{
	auto entity = make_shared<Entity>();
	entity->AddComponent(make_shared<CDebris>(
		DEBRIS_NUM_FRAGMENGS, 
		DEBRIS_TTL,
		c,
		radius));

	entity->AddComponent(make_shared<CPose>());
	
	return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateShipDebris()
{
	auto entity = make_shared<Entity>();
	entity->AddComponent(make_shared<CDebris>(
		SHIP_DEBRIS_NUM_FRAGMENGS, 
		SHIP_DEBRIS_TTL,
		SHIP_DEBRIS_COLOR,
		kShip.radius,
		true));

	entity->AddComponent(make_shared<CPose>());

	return entity;
}