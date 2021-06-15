/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// AST Utilities includes
#include <EntityFactoryService.h>
#include <Shape2Generator.h>
#include <Camera2Service.h>

// Local includes
#include "Ship.h"
#include "Pose2.h"
#include "Body2.h"
#include "Mesh2.h"
#include "Wrap.h"
#include "WrapSystem.h"
#include "Gun.h"
#include "Bullet.h"
#include "GameManager.h"

using namespace astu;
using namespace std;

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

GameManager::GameManager()
    : BaseService("Game Manager")
{
    // Intentionally left empty.
}

void GameManager::OnStartup()
{
    ASTU_SERVICE(WrapSystem)
        .SetWrapSize(
            WORLD_VIEW_WIDTH + SHIP_RADIUS * 2, 
            WORLD_VIEW_HEIGHT + SHIP_RADIUS * 2);

    RegisterEntityPrototypes();
    ConfigureGameWorld();
    SpawnPlayer();
}

void GameManager::OnShutdown()
{
    DeregisterEntityPrototypes();
}

void GameManager::RegisterEntityPrototypes()
{
    auto & entityFactory = ASTU_SERVICE(EntityFactoryService);
    entityFactory.RegisterPrototype("Ship", CreatePlayerShip());
    entityFactory.RegisterPrototype("BitAsteroid", CreateBigAsteroid());    
    entityFactory.RegisterPrototype("Bullet", CreateBullet());    
}

void GameManager::DeregisterEntityPrototypes()
{
    auto & entityFactory = ASTU_SERVICE(EntityFactoryService);
    entityFactory.DeregisterPrototype("BitAsteroid");
    entityFactory.DeregisterPrototype("Ship");
}

shared_ptr<Entity> GameManager::CreateBigAsteroid()
{
    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Pose2>() );
    return entity;
}

shared_ptr<Entity> GameManager::CreatePlayerShip()
{
    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Ship>(0, SHIP_TORQUE, SHIP_THRUST) );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Gun>(
        GUN_FIRERATE, GUN_MUZZLE_VELOCITY, Vector2f(0, -SHIP_RADIUS - BULLET_HEIGHT / 2)));

    entity->GetComponent<Body2>().SetAngularDamping(SHIP_ANGULAR_DAMPING);
    entity->GetComponent<Body2>().SetLinearDamping(SHIP_LINEAR_DAMPING);
    // Standard visualization.
    // entity->AddComponent( make_shared<Mesh2>(Polyline2Builder()
    //     .VertexBuffer( CreateShipMesh() )
    //     .Color(WebColors::White)
    //     .Build()) );

    // Debug visualization.
    entity->AddComponent( make_shared<Mesh2>(Node2Builder()
        .AttachChild( Polyline2Builder()
            .Color(WebColors::Orange)
            .VertexBuffer( Shape2Generator().GenCircle(SHIP_RADIUS) )
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


    return entity;
}

shared_ptr<Entity> GameManager::CreateBullet()
{
    auto entity = make_shared<Entity>();
    entity->AddComponent( make_shared<Pose2>() );
    entity->AddComponent( make_shared<Body2>() );
    entity->AddComponent( make_shared<Wrap>() );
    entity->AddComponent( make_shared<Bullet>(BULLET_TTL) );

    entity->AddComponent( make_shared<Mesh2>(Polyline2Builder()
        .VertexBuffer( Shape2Generator().GenRectangle(BULLET_WIDTH, BULLET_HEIGHT) )
        .Color(WebColors::White)
        .Build()) );


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
