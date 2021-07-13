/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "GameManager.h"
#include "Ship.h"
#include "Pose2.h"
#include "Body2.h"
#include "Collider.h"
#include "Mesh2.h"
#include "Wrap.h"
#include "WrapSystem.h"
#include "Gun.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Fadable.h"

// AST Utilities includes
#include <AstUtils.h>
#include <EntityFactoryService.h>
#include <ShapeGenerator2D.h>
#include <CameraService2D.h>
#include <TaskService.h>
#include <Tasks.h>

using namespace astu;
using namespace std;

// Set to true for debug visualization
#define DEBUG_VISUALS           false

// Game Mechanics Constants
#define SPAWN_ASTEROIDS_DELAY   2

#define SHIP_RADIUS             0.35f
#define SHIP_TORQUE             70.0f
#define SHIP_STEER_SPEED        3.0f
#define SHIP_THRUST             7.0f
#define SHIP_THRUST_SPEED       SHIP_STEER_SPEED
#define SHIP_ANGULAR_DAMPING    15.0f
#define SHIP_LINEAR_DAMPING     1.0f
#define GUN_FIRERATE            3.5f
#define GUN_MUZZLE_VELOCITY     12.0f

#define BULLET_WIDTH            0.025f
#define BULLET_HEIGHT           0.15f
#define BULLET_TTL              1.5f

#define NUM_ASTEROID_SEGMENTS   27
#define MIN_NUM_ASTEROIDS       3
#define ASTEROID_MIN_VEL        0.1f
#define ASTEROID_MAX_VEL        1.5f
#define ASTEROID_MIN_ANG_VEL    0.5f
#define ASTEROID_MAX_ANG_VEL    1.5f
#define BIG_ASTEROID_RADIUS     0.7f
#define MEDIUM_ASTEROID_RADIUS  (BIG_ASTEROID_RADIUS * 0.618f)
#define SMALL_ASTEROID_RADIUS   (MEDIUM_ASTEROID_RADIUS * 0.618f)

#define DEBRIS_RADIUS           0.05f

#define WORLD_VIEW_WIDTH        16
#define WORLD_VIEW_HEIGHT       9
#define WORLD_WIDTH             (WORLD_VIEW_WIDTH + BIG_ASTEROID_RADIUS * 2)
#define WORLD_HEIGHT            (WORLD_VIEW_HEIGHT + BIG_ASTEROID_RADIUS * 2)

// Collision Categories
#define BULLET_CAT      1 << 0
#define ASTEROID_CAT    1 << 1
#define SHIP_CAT        1 << 2

// Some additional constants
#define TASK_NAME               "GameManagerTask"

GameManager::GameManager()
    : BaseService("Game Manager")
{
    // Intentionally left empty.
}

void GameManager::OnStartup()
{
    playerEvents = ASTU_GET_SERVICE(SignalService<PlayerEvent>);

    ASTU_SERVICE(WrapSystem)
        .SetWrapSize(WORLD_WIDTH, WORLD_HEIGHT);

    RegisterEntityPrototypes();
    ConfigureGameWorld();
    curLevel = 0;
    numAsteroids = 0;
    SpawnPlayer();

    ASTU_SERVICE(TaskService).AddTask(DelegateTaskBuilder()
        .Name(TASK_NAME)
        .Delegate([this](){ SpawnAsteroids(); } )
        .Delay(SPAWN_ASTEROIDS_DELAY)
        .Build()
        );

    FirePlayerEvent();
}

void GameManager::OnShutdown()
{
    ASTU_SERVICE(TaskService).RemoveAll(TASK_NAME);    
    DeregisterEntityPrototypes();
    playerEvents = nullptr;
}

void GameManager::RegisterEntityPrototypes()
{
    auto & entityFactory = ASTU_SERVICE(EntityFactoryService);
    entityFactory.RegisterPrototype("Ship", CreatePlayerShip());
    entityFactory.RegisterPrototype("BigAsteroid", CreateAsteroid(Asteroid::BIG, BIG_ASTEROID_RADIUS));    
    entityFactory.RegisterPrototype("MediumAsteroid", CreateAsteroid(Asteroid::MEDIUM, MEDIUM_ASTEROID_RADIUS));    
    entityFactory.RegisterPrototype("SmallAsteroid", CreateAsteroid(Asteroid::SMALL, SMALL_ASTEROID_RADIUS));    
    entityFactory.RegisterPrototype("Bullet", CreateBullet());    
    entityFactory.RegisterPrototype("Debris", CreateDebris());    
}

void GameManager::DeregisterEntityPrototypes()
{
    auto & entityFactory = ASTU_SERVICE(EntityFactoryService);
    entityFactory.DeregisterPrototype("BigAsteroid");
    entityFactory.DeregisterPrototype("Ship");
}

shared_ptr<Entity> GameManager::CreateAsteroid(Asteroid::Type type, float radius)
{
    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Collider>(radius, ASTEROID_CAT, BULLET_CAT | SHIP_CAT) );
    entity->AddComponent( make_shared<Asteroid>(
        type, 
        ASTEROID_MAX_VEL, 
        ASTEROID_MIN_VEL, 
        ASTEROID_MAX_ANG_VEL, 
        ASTEROID_MIN_ANG_VEL)
        );

    // Asteroids should move forever
    entity->GetComponent<Body2>().SetAngularDamping(0);
    entity->GetComponent<Body2>().SetLinearDamping(0);

    if (DEBUG_VISUALS) {
        entity->AddComponent( make_shared<Mesh2>(NodeBuilder2D()
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Orange)
                .VertexBuffer( ShapeGenerator2D().GenCircle(radius) )
                .Build())
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Green)
                .VertexBuffer( ShapeGenerator2D().GenCircle(radius * 0.05f) )
                .Build())
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Black)
                .VertexBuffer( CreateAsteroidMesh(radius) )
                .Build())
            .Build() ));
    } else {
        entity->AddComponent( make_shared<Mesh2>(PolylineBuilder2D()
            .VertexBuffer( CreateAsteroidMesh(radius) )
            .Color(WebColors::Black)
            .Build()) );
    }

    return entity;

}

shared_ptr<Entity> GameManager::CreatePlayerShip()
{
    const float kColliderRadius = SHIP_RADIUS * 0.8f;

    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Ship>(SHIP_THRUST, SHIP_TORQUE, SHIP_STEER_SPEED, SHIP_THRUST_SPEED) );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Collider>(kColliderRadius, SHIP_CAT, ASTEROID_CAT) );
    entity->AddComponent( make_shared<Gun>(
        GUN_FIRERATE, 
        GUN_MUZZLE_VELOCITY, 
        Vector2f(0, -SHIP_RADIUS - BULLET_HEIGHT / 2))
        );

    entity->GetComponent<Body2>().SetAngularDamping(SHIP_ANGULAR_DAMPING);
    entity->GetComponent<Body2>().SetLinearDamping(SHIP_LINEAR_DAMPING);

    if (DEBUG_VISUALS) {
        entity->AddComponent( make_shared<Mesh2>(NodeBuilder2D()
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Orange)
                .VertexBuffer( ShapeGenerator2D().GenCircle(kColliderRadius) )
                .Build())
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Green)
                .VertexBuffer( ShapeGenerator2D().GenCircle(SHIP_RADIUS * 0.05f) )
                .Build())
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Black)
                .VertexBuffer( CreateShipMesh() )
                .Build())
            .Build() ));
    } else {
        entity->AddComponent( make_shared<Mesh2>(PolylineBuilder2D()
            .VertexBuffer( CreateShipMesh() )
            .Color(WebColors::Black)
            .Build()) );
    }

    return entity;
}

shared_ptr<Entity> GameManager::CreateBullet()
{
    const float kColliderRadius = (BULLET_WIDTH + BULLET_HEIGHT) * 0.5f;

    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Collider>(kColliderRadius, BULLET_CAT, ASTEROID_CAT) );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Bullet>(BULLET_TTL) );

    if (DEBUG_VISUALS) {
        entity->AddComponent( make_shared<Mesh2>(NodeBuilder2D()
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Orange)
                .VertexBuffer( ShapeGenerator2D().GenCircle(kColliderRadius) )
                .Build())
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Green)
                .VertexBuffer( ShapeGenerator2D().GenCircle(kColliderRadius * 0.05f) )
                .Build())
            .AttachChild( PolylineBuilder2D()
                .Color(WebColors::Black)
                .VertexBuffer( ShapeGenerator2D().GenRectangle(BULLET_WIDTH, BULLET_HEIGHT) )
                .Build())
            .Build() ));
    } else {
        entity->AddComponent( make_shared<Mesh2>(PolylineBuilder2D()
            .Color(WebColors::Black)
            .VertexBuffer( ShapeGenerator2D().GenRectangle(BULLET_WIDTH, BULLET_HEIGHT) )
            .Build()) );
    }

    return entity;
}

shared_ptr<astu::Entity> GameManager::CreateDebris()
{
    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Fadable>(0.5f) );

    entity->AddComponent( make_shared<Mesh2>(PolylineBuilder2D()
        .Color(WebColors::Black)
        .VertexBuffer( ShapeGenerator2D().GenStar(DEBRIS_RADIUS))
        .Build()) );

    return entity;
}

void GameManager::ConfigureGameWorld()
{
    GetCamera().ShowFitting(WORLD_VIEW_WIDTH, WORLD_VIEW_HEIGHT);
}

void GameManager::SpawnPlayer()
{
    auto entity = ASTU_SERVICE(EntityFactoryService).CreateEntity("Ship");
    entity->GetComponent<Pose2>()
        .transform.SetTranslation(0, 0).SetRotation(0);

    ASTU_SERVICE(EntityService).AddEntity(entity);
}

void GameManager::SpawnAsteroids()
{
    for (int i = 0; i < MIN_NUM_ASTEROIDS + curLevel; ++i) {
        // Spawn asteroid on one of the four sides in order to avoid hitting
        // the player's ship and hide the sudden popping up of the asteriods.

        Vector2f p = GetRandomSafePosition();
        SpawnAsteroid(p);
    }
}

astu::Vector2f GameManager::GetRandomSafePosition()
{
        Vector2f p;
        switch ( GetRandomInt(0, 4) ) {
        case 0:
            // Create random position on left side.
            return Vector2f(
                -WORLD_WIDTH / 2, 
                GetRandomFloat(WORLD_HEIGHT / 2, -WORLD_HEIGHT / 2)
            );

        case 1:
            // Create random position on right side.
            return Vector2f(
                WORLD_WIDTH / 2, 
                GetRandomFloat(WORLD_HEIGHT / 2, -WORLD_HEIGHT / 2)
            );

        case 2:
            // Create random position at top.
            return Vector2f(
                GetRandomFloat(WORLD_WIDTH / 2, -WORLD_WIDTH / 2), 
                -WORLD_HEIGHT / 2
            );

        case 3:
            // Create random position at bottom.
            return Vector2f(
                GetRandomFloat(WORLD_WIDTH / 2, -WORLD_WIDTH / 2), 
                WORLD_HEIGHT / 2
            );

        default:
            // Fall-back, should never happen
            return Vector2f(0, 0);
        }
}

void GameManager::SpawnAsteroid(const astu::Vector2f & p)
{
    auto entity = ASTU_SERVICE(EntityFactoryService)
        .CreateEntity("BigAsteroid");

    // Set position.
    entity->GetComponent<Pose2>().transform.SetTranslation(p);

    // Add entity to game world.
    ASTU_SERVICE(EntityService).AddEntity(entity);

    // Emit game event
    ASTU_SERVICE(SignalService<GameEvent>)
        .QueueSignal(GameEvent(GameEvent::BIG_ASTEROID_SPAWNED, p));

}

shared_ptr<astu::VertexBuffer2D> GameManager::CreateShipMesh()
{
    auto & vbBuilder = ASTU_SERVICE(VertexBufferBuilder2D);
    vbBuilder.Reset();

    Vector2f v;
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS) );
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS).RotateDeg(120) );
    vbBuilder.AddVertex( v.Set(0, SHIP_RADIUS * 0.35f) );
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS).RotateDeg(-120) );
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS) );

    return vbBuilder.Build();
}

std::shared_ptr<astu::VertexBuffer2D> GameManager::CreateAsteroidMesh(float r)
{
    auto & vbBuilder = ASTU_SERVICE(VertexBufferBuilder2D);
    vbBuilder.Reset();

    // First step: create circular asteroid
    const float deltaAngle = 360.0f / NUM_ASTEROID_SEGMENTS;
    Vector2f v;
    for (int i = 0; i < NUM_ASTEROID_SEGMENTS; ++i) {
        v.Set(0, r);
        v.RotateDeg(deltaAngle * i);
        vbBuilder.AddVertex(v);
    }

    // Second step: deform vertices
    const int n = NUM_ASTEROID_SEGMENTS;
    const int stepSize = NUM_ASTEROID_SEGMENTS / 5;
    const float maxDeform = 0.3f;   // max deformation +/- %
    const float influence = 0.9f;   // the amount neighbors get influenced
    const float numNeighbors = 3;   // the number of neighbors to influence

    for (int i = 0; i < n; i += stepSize) {
        float deform = GetRandomFloat(-maxDeform, maxDeform);

        Vector2f v = vbBuilder.GetVertex(i);
        Vector2f delta(v);
        delta.SetLength(v.Length() * deform);
        vbBuilder.SetVertex(i, v + delta);

        float infl = influence;
        for (int j = 1; j <= numNeighbors; ++j) {
            int idx = ((i - j) % n + n) % n;
            v = vbBuilder.GetVertex(idx);
            vbBuilder.SetVertex(idx, v + (delta * infl));

            idx = ((i + j) % n + n) % n;
            v = vbBuilder.GetVertex(idx);
            vbBuilder.SetVertex(idx, v + (delta * infl));

            infl *= infl;
        }
    }

    // Close polygon.
    vbBuilder.AddVertex( vbBuilder.GetVertex(0) );

    // Build and return vertex buffer of asteroid shape.
    return vbBuilder.Build();


    // auto & vbBuilder = ASTU_SERVICE(VertexBufferBuilder2D);
    // vbBuilder.Reset();

    // const float deformFactor = 0.3f;
    // const float stepDeform = 0.1f;
    // const float minR = r * (1.0f - deformFactor);
    // const float maxR = r * (1.0f + deformFactor);
    // const float da = 360.0f / NUM_ASTEROID_SEGMENTS;
    // float lastR = r;

    // Vector2f v;
    // for (int i = 0; i < NUM_ASTEROID_SEGMENTS; ++i) {
    //     const float low = std::max(minR, lastR * (1.0f - stepDeform));
    //     const float hi = std::min(maxR, lastR * (1.0f + stepDeform));

    //     lastR = GetRandomFloat(low, hi);
    //     v.Set(0, lastR);
    //     v.RotateDeg(da * i);
    //     vbBuilder.AddVertex( v );
    // }

    // // Close polygon.
    // vbBuilder.AddVertex( vbBuilder.GetVertex(0) );

    // return vbBuilder.Build();
}

bool GameManager::OnSignal(const GameEvent & signal)
{
    // Take care of the current number of asteroids.
    switch (signal.type) {

        case GameEvent::BIG_ASTEROID_SPAWNED:
        case GameEvent::MEDIUM_ASTEROID_SPAWNED:
        case GameEvent::SMALL_ASTEROID_SPAWNED:
            ++numAsteroids;
            break;

        case GameEvent::BIG_ASTEROID_DESTROYED:
        case GameEvent::MEDIUM_ASTEROID_DESTROYED:
        case GameEvent::SMALL_ASTEROID_DESTROYED:
            --numAsteroids;
            break;

        default:
            break;
    }

    if (numAsteroids <= 0) {
        // All asteroids have been cleard; proceed to the next level.
        numAsteroids = 0;
        ++curLevel;

        ASTU_SERVICE(TaskService).AddTask(DelegateTaskBuilder()
            .Name(TASK_NAME)
            .Delegate([this](){ SpawnAsteroids(); } )
            .Delay(SPAWN_ASTEROIDS_DELAY)
            .Build()
            );
    }

    FirePlayerEvent();

    return false;
}

void GameManager::FirePlayerEvent()
{
    playerEvents->QueueSignal(PlayerEvent(curLevel, numAsteroids, 0));
}