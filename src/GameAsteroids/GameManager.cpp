/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// AST Utilities includes
#include <AstUtils.h>
#include <EntityFactoryService.h>
#include <Shape2Generator.h>
#include <Camera2Service.h>
#include <TaskService.h>
#include <Tasks.h>

// Local includes
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
#include "GameManager.h"

using namespace astu;
using namespace std;

#define TASK_NAME               "GameManagerTask"
#define SPAWN_ASTEROIDS_DELAY   5

// Set to true for debug visualization
#define DEBUG_VISUALS           false


// Game Mechanics Constants
#define WORLD_VIEW_WIDTH        16
#define WORLD_VIEW_HEIGHT       9

#define SHIP_RADIUS             0.35f
#define SHIP_TORQUE             60.0f
#define SHIP_THRUST             7.0f
#define SHIP_ANGULAR_DAMPING    10.0f
#define SHIP_LINEAR_DAMPING     1.0f
#define GUN_FIRERATE            5.0f
#define GUN_MUZZLE_VELOCITY     15.0f

#define BULLET_WIDTH            0.025f
#define BULLET_HEIGHT           0.15f
#define BULLET_TTL              1.0f

#define NUM_ASTEROID_SEGMENTS   13
#define MIN_NUM_ASTEROIDS       3
#define ASTEROID_MIN_VEL        0.05f
#define ASTEROID_MAX_VEL        1.5f
#define ASTEROID_MIN_ANG_VEL    -1.5f
#define ASTEROID_MAX_ANG_VEL    1.0f
#define BIG_ASTEROID_RADIUS     0.7f
#define MEDIUM_ASTEROID_RADIUS  (BIG_ASTEROID_RADIUS * 0.618f)
#define SMALL_ASTEROID_RADIUS  (MEDIUM_ASTEROID_RADIUS * 0.618f)


GameManager::GameManager()
    : BaseService("Game Manager")
{
    // Intentionally left empty.
}

void GameManager::OnStartup()
{
    playerEvents = ASTU_GET_SERVICE(SignalService<PlayerEvent>);

    ASTU_SERVICE(WrapSystem)
        .SetWrapSize(
            WORLD_VIEW_WIDTH + SHIP_RADIUS * 2, 
            WORLD_VIEW_HEIGHT + SHIP_RADIUS * 2);

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
    entity->AddComponent( make_shared<Collider>(radius) );
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
        entity->AddComponent( make_shared<Mesh2>(Node2Builder()
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Orange)
                .VertexBuffer( Shape2Generator().GenCircle(radius) )
                .Build())
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Green)
                .VertexBuffer( Shape2Generator().GenCircle(radius * 0.05f) )
                .Build())
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Black)
                .VertexBuffer( CreateAsteroidMesh(radius) )
                .Build())
            .Build() ));
    } else {
        entity->AddComponent( make_shared<Mesh2>(Polyline2Builder()
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
    entity->AddComponent( make_shared<Ship>(0, SHIP_TORQUE, SHIP_THRUST) );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Collider>(kColliderRadius) );
    entity->AddComponent( make_shared<Gun>(
        GUN_FIRERATE, 
        GUN_MUZZLE_VELOCITY, 
        Vector2f(0, -SHIP_RADIUS - BULLET_HEIGHT / 2))
        );

    entity->GetComponent<Body2>().SetAngularDamping(SHIP_ANGULAR_DAMPING);
    entity->GetComponent<Body2>().SetLinearDamping(SHIP_LINEAR_DAMPING);

    if (DEBUG_VISUALS) {
        entity->AddComponent( make_shared<Mesh2>(Node2Builder()
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Orange)
                .VertexBuffer( Shape2Generator().GenCircle(kColliderRadius) )
                .Build())
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Green)
                .VertexBuffer( Shape2Generator().GenCircle(SHIP_RADIUS * 0.05f) )
                .Build())
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Black)
                .VertexBuffer( CreateShipMesh() )
                .Build())
            .Build() ));
    } else {
        entity->AddComponent( make_shared<Mesh2>(Polyline2Builder()
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
    entity->AddComponent( make_shared<Collider>(kColliderRadius) );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Bullet>(BULLET_TTL) );

    if (DEBUG_VISUALS) {
        entity->AddComponent( make_shared<Mesh2>(Node2Builder()
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Orange)
                .VertexBuffer( Shape2Generator().GenCircle(kColliderRadius) )
                .Build())
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Green)
                .VertexBuffer( Shape2Generator().GenCircle(kColliderRadius * 0.05f) )
                .Build())
            .AttachChild( Polyline2Builder()
                .Color(WebColors::Black)
                .VertexBuffer( Shape2Generator().GenRectangle(BULLET_WIDTH, BULLET_HEIGHT) )
                .Build())
            .Build() ));
    } else {
        entity->AddComponent( make_shared<Mesh2>(Polyline2Builder()
            .Color(WebColors::Black)
            .VertexBuffer( Shape2Generator().GenRectangle(BULLET_WIDTH, BULLET_HEIGHT) )
            .Build()) );
    }

    return entity;
}

void GameManager::ConfigureGameWorld()
{
    ASTU_SERVICE( Camera2Service )
        .GetCamera()->ShowFitting(WORLD_VIEW_WIDTH, WORLD_VIEW_HEIGHT);
}

void GameManager::SpawnPlayer()
{
    auto entity = ASTU_SERVICE(EntityFactoryService).CreateEntity("Ship");
    entity->GetComponent<Pose2>()
        .transform.SetTranslation(0, 0).SetRotation(0);

    entity->GetComponent<Ship>().playerId = 0;

    ASTU_SERVICE(EntityService).AddEntity(entity);
}

void GameManager::SpawnAsteroids()
{
    for (int i = 0; i < MIN_NUM_ASTEROIDS + curLevel; ++i) {
        Vector2f p;
        p.x = -WORLD_VIEW_WIDTH * 0.5, WORLD_VIEW_HEIGHT * 0.5;
        p.y = -WORLD_VIEW_WIDTH * 0.5, WORLD_VIEW_HEIGHT * 0.5;
        SpawnAsteroid(p);
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

shared_ptr<astu::VertexBuffer2> GameManager::CreateShipMesh()
{
    auto & vbBuilder = ASTU_SERVICE(VertexBuffer2Builder);
    vbBuilder.Reset();

    Vector2f v;
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS) );
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS).RotateDeg(120) );
    vbBuilder.AddVertex( v.Set(0, SHIP_RADIUS * 0.35f) );
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS).RotateDeg(-120) );
    vbBuilder.AddVertex( v.Set(0, -SHIP_RADIUS) );

    return vbBuilder.Build();
}

std::shared_ptr<astu::VertexBuffer2> GameManager::CreateAsteroidMesh(float r)
{
    // return Shape2Generator().GenCircle(r);

    auto & vbBuilder = ASTU_SERVICE(VertexBuffer2Builder);
    vbBuilder.Reset();

    Vector2f v;
    const float deformFactor = 0.2f;
    const float da = 360.0f / NUM_ASTEROID_SEGMENTS;
    for (int i = 0; i < NUM_ASTEROID_SEGMENTS; ++i) {
        v.Set(0, GetRandomFloat(r * (1.0f - deformFactor), r * (1.0f + deformFactor)));
        v.RotateDeg(da * i);
        vbBuilder.AddVertex( v );
    }

    // Close polygon.
    vbBuilder.AddVertex( vbBuilder.GetVertex(0) );

    return vbBuilder.Build();
}

bool GameManager::OnSignal(const GameEvent & signal)
{
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
    }

    if (numAsteroids <= 0) {
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