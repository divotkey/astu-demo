/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "ShipSystem.h"
#include "CShip.h"

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily ShipSystem::FAMILY = EntityFamily::Create<CShip, CBody, CPose>();

ShipSystem::ShipSystem(int updatePriority)
	  : BaseService("Ship System")
	  , IteratingEntitySystem(FAMILY, updatePriority)    
{
	  // Intentionally left empty.
}

void ShipSystem::OnStartup()
{
	auto& imps = ASTU_SERVICE(InputMappingService);
	thrustAxis = imps.BindAxis("Thrust");
	turnAxis = imps.BindAxis("Turn");
}

void ShipSystem::OnShutdown()
{
	auto& imps = ASTU_SERVICE(InputMappingService);
	imps.RemoveAxisBinding(thrustAxis);
	thrustAxis = nullptr;
	imps.RemoveAxisBinding(turnAxis);
	turnAxis = nullptr;
}

void ShipSystem::ProcessEntity(Entity & entity)
{
    auto& body = entity.GetComponent<CBody>();
    auto& ship = entity.GetComponent<CShip>();
	
	// Update current thrust, used for thrust visualization etc.
	ship.curThrust = thrustAxis->GetValue() * ship.maxThrust;

	// Apply current torque.
    body.ApplyTorque(turnAxis->GetValue() * ship.maxTorque);

	// Apply current thrust.
	body.ApplyForce( body.GetWorldVector(0, -ship.curThrust));
}

void ShipSystem::DestroyShip(astu::Entity& entity)
{
    GetEntityService().RemoveEntity(entity);
    const auto& pos = entity.GetComponent<CPose>().transform.GetTranslation();
	EmitSignal(GameEvent(GameEvent::Type::ShipDestroyed, pos));
}

bool ShipSystem::OnCollision(astu::Entity& entityA, astu::Entity& entityB)
{
    if (entityA.HasComponent<CShip>()) {
		DestroyShip(entityA);
    }
    if (entityB.HasComponent<CShip>()) {
		DestroyShip(entityB);
    }
    return false;
}