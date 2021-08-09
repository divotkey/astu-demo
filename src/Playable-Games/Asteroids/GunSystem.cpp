/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "GunSystem.h"
#include "CGun.h"

// AST Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily GunSystem::FAMILY = EntityFamily::Create<CGun, CPose>();

GunSystem::GunSystem(int updatePriority)
	  : BaseService("Gun System")
	  , IteratingEntitySystem(FAMILY, updatePriority)    
{
	  // Intentionally left empty.
}

void GunSystem::OnStartup()
{
	fireAction = ASTU_SERVICE(InputMappingService).BindAction("Fire");
	fireAction->SetDelegate([this](ActionBinding &binding){
		if (binding.IsPressed()) {
			trigger = true;
		}
	});
	trigger = false;
}

void GunSystem::OnShutdown()
{
	ASTU_SERVICE(InputMappingService).RemoveActionBinding(fireAction);
	fireAction = nullptr;
}

void GunSystem::ProcessEntity(Entity & entity)
{
	// The gun is cooling down, no matter if the trigger has been pulled or not.
    auto& gun = entity.GetComponent<CGun>();
	gun.cooldown -= GetElapsedTimeF();
	if (gun.cooldown > 0) {
		return;
	}

	// Use this if condition to allow permanent firing, when button is pressed.
	// if (!fireAction->IsPressed()) {
	// 	return;
	// }
	if (!trigger) {
		return;
	}
	trigger = false;

	// Set cool down according to fire rate.
	gun.cooldown = gun.fireRate;

	// Determine spawn point of bullet and orientation.
	auto pose = entity.GetComponent<CPose>();	
	Vector2f spawnPoint = pose.transform.TransformPoint(gun.mountPoint);

	// Create and add bullet.
	auto bulletEntity = AddEntity("Bullet", spawnPoint, pose.transform.GetRotation());

	// Set velocity of bullet.
	auto& bulletBody = bulletEntity->GetComponent<CBody>();
	Vector2f velocity = pose.transform.TransformVector(gun.direction) * gun.muzzleVelocity;
	bulletBody.SetLinearVelocity(velocity);
}