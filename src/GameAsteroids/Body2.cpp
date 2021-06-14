/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "Body2.h"

using namespace astu;

void Body2::SetMass(float m)
{
    mass = m;
    if (mass == 0) {
        invMass = 0;
    } else {
        invMass = 1 / mass;
    }
}

void Body2::SetMomentOfInertia(float moi)
{
    this->moi = moi;
    if (moi == 0) {
        invMoi = 0;
    } else {
        invMoi = 1 / moi;
    }
}

void Body2::SetLinearDamping(float d)
{
    dmp[0] = dmp[1] = d;
}

void Body2::SetAngularDamping(float d)
{
    dmp[2] = d;    
}

void Body2::SetLinearPosition(float x, float y)
{
    pos[0] = x;
    pos[1] = y;
}

void Body2::SetAngularPosition(float phi)
{
    pos[2] = phi;
}

void Body2::SetLinearVelocity(float vx, float vy)
{
    vel[0] = vx;
    vel[1] = vy;
}

void Body2::SetAngularVelocity(float omega)
{
    vel[2] = omega;
}

void Body2::StoreToTransform(Transform2f &tx) const
{
    tx.SetTranslation(pos[0], pos[1]);
    tx.SetRotation(pos[2]);
}

void Body2::RestoreFromTransform(const astu::Transform2f &tx)
{
    pos[0] = tx.GetTranslation().x;
    pos[1] = tx.GetTranslation().y;
    pos[2] = tx.GetRotation();
}

 void Body2::Step(float dt)
 {
    // Semi-implicit Euler integration.

    // 1.) Update velocities based on current acceleration/forces.
    vel[0] += (acc[0] - vel[0] * dmp[0]) * dt;
    vel[1] += (acc[1] - vel[1] * dmp[1]) * dt;
    vel[2] += (acc[2] - vel[2] * dmp[2]) * dt;

    // 2.) Update position based on newly calculated velocities.
    pos[0] += vel[0] * dt;
    pos[1] += vel[1] * dt;
    pos[2] += vel[2] * dt;
 }

void Body2::ClearForces()
{
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
}

void Body2::ApplyTorque(float t)
{
    acc[2] += t * invMoi;
}

void Body2::ApplyForce(float fx, float fy)
{
    acc[0] += fx * invMass;
    acc[1] += fy * invMass;
}

Vector2f Body2::GetLocalVector(float vx, float vy)
{
    Vector2f result(vx, vy);
    result.Rotate(-pos[2]);

    return result;
}

Vector2f Body2::GetWorldVector(float vx, float vy)
{
    Vector2f result(vx, vy);
    result.Rotate(pos[2]);

    return result;
}

Vector2f Body2::GetWorldPoint(float px, float py)
{
    Vector2f result(px, py);
    result.Rotate(pos[2]);
    result.Add(pos[0], pos[1]);

    return result;
}