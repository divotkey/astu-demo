/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuMath.h>

// C++ Standard Library includes
#include <memory>
#include <vector>
#include <functional>

class Particle {
public:

    /** The position of this particle. */
    astu::Vector2f pos;

    /** The velocity of this particle. */
    astu::Vector2f vel;

    /** The current age of this particle. */
    float age;

    /** The total time to live for this particle. */
    float ttl;
};

class ParticleSystem {
public:

    /**
     * Obtains a particle system from the pool.
     * 
     * @param n the number of particles in the system
     */
    static std::unique_ptr<ParticleSystem> Obtain(int n);

    /**
     * Places a particle system back into the pool.
     * 
     * @param ps    the particle system to be freed.
     */
    static void Free(std::unique_ptr<ParticleSystem> ps);

    /**
     * Updates this system's particle positions.
     * 
     * @param dt    the elapsed time since the last update in seconds
     * @return `true` if there are any active particles left.
     */
    bool Update(float dt);

    /**
     * Visits all particles, active or inactive.
     * 
     * @param visitor   the visitor funciton
     */
    void VisitAll(std::function<void (Particle& p)> visitor);

    /**
     * Visits all active particles. 
     * 
     * @param visitor   the visitor funciton
     */
    void VisitActive(std::function<void (Particle& p)> visitor);

    /**
     * Visits all inactive particles. 
     * 
     * @param n         the maximum number of particles to visit
     * @param visitor   the visitor funciton
     */
    void VisitInactive(int n, std::function<void (Particle& p)> visitor);

private:
    /** The pool of particle systems. */
    static std::vector<std::unique_ptr<ParticleSystem>> pool;

    /** The particles of this particle system. */
    std::vector<Particle> particles;

    /**
     * Private constructor.
     * 
     * @param n the number of particles in the system
     */
    ParticleSystem(int n);
};