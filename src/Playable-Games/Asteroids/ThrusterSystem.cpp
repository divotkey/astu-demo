/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "ThrusterSystem.h"
#include "CShip.h"

// AST Utilities includes
#include <AstuMath.h>
#include <AstuGraphics.h>

// C++ Standard Library includes
#include <algorithm>

using namespace astu2d;
using namespace astu;
using namespace std;

#define MIN_RADIUS_FACTOR 		0.1f
#define FRAGMENT_POINT_SIZE 	0.05f
#define FRAGMENT_SPEED			5.0f
#define FRAGMENT_SPEED_SPREAD	0.25f
#define FRAGMENT_ANGLE			MathUtils::ToRadians(40.0f)
#define FRAGMENTS_PER_THRUST	50.0f
#define FRAGMENTS_TTL_SPREAD	0.2f

#define SPREAD(a, p) Random::GetInstance().NextFloat(a * (1.0f - p), a * (1.0f + p))
#define RANGE(a, b) Random::GetInstance().NextFloat(a, b)
#define RND_VECT(a) Random::GetInstance().NextVector2f(a)

const EntityFamily ThrusterSystem::FAMILY = EntityFamily::Create<CThruster, CPose, CShip>();

ThrusterSystem::ThrusterSystem(int updatePriority)
	  : BaseService("Thruster System")
	  , IteratingEntitySystem(FAMILY, updatePriority)    
	  , EntityListener(FAMILY)
{
	// Intentionally left empty.
}

void ThrusterSystem::OnStartup()
{
	// Intentionally left empty.
}

void ThrusterSystem::OnShutdown()
{
	// Intentionally left empty.
	for (auto& cooldown : cooldowns) {
		ParticleSystem::Free(move(cooldown.particleSystem));
	}
	cooldowns.clear();
}

void ThrusterSystem::OnEntityAdded(shared_ptr<Entity> entity)
{
	auto& thruster = entity->GetComponent<CThruster>();
	auto& pose = entity->GetComponent<CPose>();

	// Add pooled particle system to thruster component.
	thruster.particleSystem = ParticleSystem::Obtain(thruster.numFragments);

	// Initialize all particles and set to inactive
	thruster.particleSystem->VisitAll([thruster](Particle& ptcl){
		ptcl.ttl = ptcl.age = 0;
	});
}

void ThrusterSystem::OnEntityRemoved(std::shared_ptr<astu::Entity> entity)
{
	auto& thruster = entity->GetComponent<CThruster>();
	assert(thruster.particleSystem);
	
	cooldowns.push_back(CoolDown(move(thruster.particleSystem), thruster.color));
}

void ThrusterSystem::OnUpdate()
{
	// Befor we use the line renderer, we must set the view transform
	// based on the camera we are using. 
	SetViewTransform(GetCamera().GetMatrix());

	// Call our base class' update method which will in turn call
	// ProcessEntity for each of our entities.
	IteratingEntitySystem::OnUpdate();

	// Update and render detached particle system with alive particles.
	UpdateCooldown();
}

void ThrusterSystem::ProcessEntity(Entity & entity)
{
	auto& pose = entity.GetComponent<CPose>();
	auto& thruster = entity.GetComponent<CThruster>();

	// Update positions of fragments.
	thruster.particleSystem->Update(GetElapsedTimeF());

	// Emit fragments.
	auto& ship = entity.GetComponent<CShip>();
	EmitFragments(ship.curThrust * FRAGMENTS_PER_THRUST, thruster, pose);

	// Render fragments.
	RenderFragments(*thruster.particleSystem, thruster.color);
}

void ThrusterSystem::EmitFragments(float rate, CThruster& thruster, const CPose& pose)
{
	// Determine number of fragments to emit.
	thruster.emitFraction += rate * GetElapsedTimeF();
	int n = static_cast<int>(thruster.emitFraction);
	thruster.emitFraction -= n;

	// Initialize new particles to represents fragments
	thruster.particleSystem->VisitInactive(n, [thruster, pose](Particle& ptcl) {
		Vector2f p = thruster.offset;
		p.Rotate(pose.transform.GetRotation());
		p += pose.transform.GetTranslation();
		p += RND_VECT(RANGE(thruster.radius * MIN_RADIUS_FACTOR, thruster.radius));

		ptcl.age = 0;
		ptcl.ttl = SPREAD(thruster.ttl, FRAGMENTS_TTL_SPREAD);
		ptcl.pos = p;
		ptcl.vel.Set(0, SPREAD(FRAGMENT_SPEED, FRAGMENT_SPEED_SPREAD));
		ptcl.vel.Rotate(pose.transform.GetRotation() +  RANGE(-FRAGMENT_ANGLE / 2, FRAGMENT_ANGLE / 2));
	});
}

void ThrusterSystem::RenderFragments(ParticleSystem& ps, const astu::Color4f& c)
{
	ps.VisitActive([this, c](Particle& ptcl){
		float a = max(0.0f, 1.0f - ptcl.age / ptcl.ttl);
		SetDrawColor(Color4f(c).SetAlpha(a));
		DrawRectangle(ptcl.pos, {FRAGMENT_POINT_SIZE, FRAGMENT_POINT_SIZE});
	});
}

void ThrusterSystem::UpdateCooldown()
{
	float dt = GetElapsedTimeF();
	for (auto it = cooldowns.begin(); it != cooldowns.end();) {
		if(it->particleSystem->Update(dt)) {
			// There are still alive particles.
			RenderFragments(*it->particleSystem, it->color);
			++it;
		} else {
			ParticleSystem::Free(move(it->particleSystem));
			it = cooldowns.erase(it);
		}
	}
}
