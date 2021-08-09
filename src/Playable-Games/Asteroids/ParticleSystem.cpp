/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "ParticleSystem.h"

// C++ Standard Library includes
#include <algorithm>


using namespace astu;
using namespace std;

vector<unique_ptr<ParticleSystem>> ParticleSystem::pool;

unique_ptr<ParticleSystem> ParticleSystem::Obtain(int n)
{
    if (pool.empty()) {
        return unique_ptr<ParticleSystem>(new ParticleSystem(n));
    } else {
        unique_ptr<ParticleSystem> ps = move(pool.back());
        pool.pop_back();
        assert(ps);
        ps->particles.resize(n);
        return ps;
    }
}

void ParticleSystem::Free(unique_ptr<ParticleSystem> ps)
{
    pool.push_back(move(ps));
}

ParticleSystem::ParticleSystem(int n)
    : particles(n)
{
    // Intentionally left empty.
}

bool ParticleSystem::Update(float dt)
{
    unsigned int cnt = 0;
    for(auto& particle : particles) {
        particle.age += dt;
        particle.pos += particle.vel * dt;

        if (particle.age <= particle.ttl) {
            ++cnt;
        }
    }

    return cnt > 0;
}

void ParticleSystem::VisitActive(std::function<void (Particle& p)> visitor)
{
    for (auto& particle : particles) {
        if (particle.age <= particle.ttl)
            visitor(particle);
    }
}

void ParticleSystem::VisitAll(std::function<void (Particle& p)> visitor)
{
    for (auto& particle : particles) {
        visitor(particle);
    }
}

void ParticleSystem::VisitInactive(int n, std::function<void (Particle& p)> visitor)
{
    for (auto& particle : particles) {
        if (n <= 0)
            break;

        if (particle.age > particle.ttl) {
            visitor(particle);
            --n;
        }
    }
}
