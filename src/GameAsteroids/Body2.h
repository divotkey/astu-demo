/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// C++ Standard Library includes.
#include <array>

// AST Utilities includes
#include <EntityService.h>
#include <Transform2.h>
#include <Vector2.h>

/**
 * An entity component which describes the physical properties of an entity.
 */
class Body2 : public astu::EntityComponent {
public:

    /**
     * Constructor.
     */
    Body2()
        : pos{0, 0, 0}
        , vel{0, 0, 0}
        , acc{0, 0, 0}
        , dmp{0, 0, 0}
        , mass(1), invMass(1), moi(1), invMoi(1)
    {
        // Intentionally left empty.
    }

    /**
     * Sets the mass of this body.
     * 
     * Setting the mass to 0 makes this body unable to move.
     * 
     * @param m the mass
     */
    void SetMass(float m);

    /**
     * Returns the mass of this body.
     * 
     * @return the mass
     */
    float GetMass() const {
        return mass;
    }

    /**
     * Sets the moment of inertia of this body.
     * 
     * Setting the moment of inertia to 0 makes this body unable to rotate.
     * 
     * @return the moment of inertia
     */
    void SetMomentOfInertia(float moi);

    /**
     * Returns the moment of inertia of this body.
     * 
     * @return the moment of inertia
     */
    float GetMomentOfInertia() const {
        return moi;
    }

    void SetLinearDamping(float d);

    void SetAngularDamping(float d);

    /**
     * Sets the position of this body's center of mass.
     * 
     * @param x the x-coordinate in world units
     * @param y the y-coordinate in world units
     */
    void SetLinearPosition(float x, float y);

    /**
     * Returns the position of this bodies center of mass in world space.
     * 
     * @return the position
     */
    astu::Vector2f GetLinearPosition() const {
        return astu::Vector2f(pos[0], pos[1]);
    }

    /**
     * Sets the oritentation of this body.
     * 
     * @param phi   the angle radians
     */
    void SetAngularPosition(float phi);

    /**
     * Returns the oritentation of this body.
     * 
     * @return the oritentation in radians
     */
    float GetAngularPosition() const {
        return pos[2];
    }

    /**
     * Sets the linear velocity of this body.
     * 
     * @param vx    the x-component of the velocity in world units per second
     * @param vy    the y-component of the velocity in world units per second
     */
    void SetLinearVelocity(float vx, float vy);

    /**
     * Sets the linear velocity of this body.
     * 
     * @param v the velocity vector in world units per second
     */
    void SetLinearVelocity(const astu::Vector2f& v) {
        SetLinearVelocity(v.x, v.y);
    }

    /**
     * Sets the angular velocity of this body.
     * 
     * @param omega the angular velocity in radians per second
     */
    void SetAngularVelocity(float omega);

    /**
     * Stores the linear and angular positon of this body to a transform.
     * 
     * @param tx    the transform which receives the positon and orientation
     */
    void StoreToTransform(astu::Transform2f &tx) const;

    /**
     * Restores the linear and angular positon of this body from a transform.
     * 
     * @param tx    the transform which provides the positon and orientation
     */
    void RestoreFromTransform(const astu::Transform2f &tx);

    /**
     * Updates position and velocity of this body.
     * 
     * @param dt    the the elapsed time in seconds
     */
    void Step(float dt);

    /**
     * Clears the accumulated angular and linear forces.
     */
    void ClearForces();

    /**
     * Applies a torque to this body.
     * 
     * @param t the torque
     */
    void ApplyTorque(float t);

    /**
     * Applies a force to the center of mass.
     * 
     * @param f the force vector in world space
     */
    void ApplyForce(const astu::Vector2f& f) {
        ApplyForce(f.x, f.y);
    }

    /**
     * Applies a force to the center of mass.
     * 
     * @param fx    the x-component of the force vector in world space
     * @param fy    the y-component of the force vector in world space
     */
    void ApplyForce(float fx, float fy);

    astu::Vector2f GetLocalVector(const astu::Vector2f& v) {
        return GetLocalVector(v.x, v.y);
    }

    astu::Vector2f GetLocalVector(float vx, float vy);

    astu::Vector2f GetWorldVector(const astu::Vector2f& v) {
        return GetWorldVector(v.x, v.y);
    }

    astu::Vector2f GetWorldVector(float vx, float vy);

    astu::Vector2f GetWorldPoint(const astu::Vector2f& p) {
        return GetWorldPoint(p.x, p.y);
    }

    astu::Vector2f GetWorldPoint(float px, float py);

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override {
        // Create copy using copy-constructor.
        return std::make_shared<Body2>(*this);
    }

private:
    /** Linear and angular position. */
    std::array<float, 3> pos; 

    /** Linear and angular velocity. */
    std::array<float, 3> vel; 

    /** Linear and angular acceleration. */
    std::array<float, 3> acc; 

    /** Linear and angular damping. */
    std::array<float, 3> dmp; 

    /** The mass of this body. */
    float mass;

    /** The inverse mass of this body. */
    float invMass;

    /** The moment of inertia of this body. */    
    float moi;

    /** The moment of inertia of this body. */
    float invMoi;
};