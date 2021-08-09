/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "DebrisSystem.h"
#include "CDebris.h"

using namespace astu2d;
using namespace astu;
using namespace std;

#define MIN_RADIUS_FACTOR 	0.1f
#define SPEED_SPREAD		0.5f
#define TTL_SPREAD			0.15f
#define FRAGMENT_POINT_SIZE 0.05f
#define FRAGMENT_SPEED		3.0f

#define SPREAD(a, p) Random::GetInstance().NextFloat(a * (1.0f - p), a * (1.0f + p))
#define RANGE(a, b) Random::GetInstance().NextFloat(a, b)
#define RND_VECT(a) Random::GetInstance().NextVector2f(a)

const EntityFamily DebrisSystem::FAMILY = EntityFamily::Create<CDebris, CPose>();

DebrisSystem::DebrisSystem(int updatePriority)
	  : BaseService("Debris System")
	  , IteratingEntitySystem(FAMILY, updatePriority)    
	  , EntityListener(FAMILY)
{
	// Intentionally left empty.
}

void DebrisSystem::OnStartup()
{
	// Intentionally left empty.
}

void DebrisSystem::OnShutdown()
{
	// Intentionally left empty.
}

void DebrisSystem::OnEntityAdded(shared_ptr<Entity> entity)
{
	auto& debris = entity->GetComponent<CDebris>();
	auto& pose = entity->GetComponent<CPose>();

	// Add pooled particle system to debris component.
	debris.particleSystem = ParticleSystem::Obtain(debris.numFragments);

	debris.particleSystem->VisitAll([debris](Particle& ptcl){
		auto& rnd = Random::GetInstance();

		float dist = RANGE(debris.radius * MIN_RADIUS_FACTOR, debris.radius);
		ptcl.pos = RND_VECT(dist);

		ptcl.vel.Set(ptcl.pos);
		ptcl.vel.SetLength(SPREAD(FRAGMENT_SPEED, SPEED_SPREAD));
		ptcl.age = 0;
		ptcl.ttl = SPREAD(debris.ttl, TTL_SPREAD);
	});
}

void DebrisSystem::OnEntityRemoved(std::shared_ptr<astu::Entity> entity)
{
	auto& debris = entity->GetComponent<CDebris>();
	assert(debris.particleSystem);
	ParticleSystem::Free(move(debris.particleSystem));
}

void DebrisSystem::OnUpdate()
{
	// Befor we use the line renderer, we must set the view transform
	// based on the camera we are using. 
	SetViewTransform(GetCamera().GetMatrix());

	// Call our base class' update method which will in turn call
	// ProcessEntity for each of our entities.
	IteratingEntitySystem::OnUpdate();
}

void DebrisSystem::ProcessEntity(Entity & entity)
{
	auto& pose = entity.GetComponent<CPose>();
	auto& debris = entity.GetComponent<CDebris>();

	// Update positions of debris fragments.
	bool aliveParticles = debris.particleSystem->Update(GetElapsedTimeF());

	const auto& wp = pose.transform.GetTranslation();

	debris.particleSystem->VisitActive([this, debris, wp](Particle& ptcl){
		float a = 1.0f - clamp(ptcl.age / ptcl.ttl, 0.0f, 1.0f);
		SetDrawColor(Color4f(debris.color).SetAlpha(a));
		DrawRectangle(wp + ptcl.pos, {FRAGMENT_POINT_SIZE, FRAGMENT_POINT_SIZE});
	});

	if (!aliveParticles) {
		ASTU_SERVICE(EntityService).RemoveEntity(entity);
	}
}