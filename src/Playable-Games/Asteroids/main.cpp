/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "EntityPrototypeService.h"	
#include "GameModeService.h"
#include "ShipSystem.h"
#include "BulletSystem.h"
#include "AsteroidSystem.h"
#include "GunSystem.h"
#include "WrapSystem.h"
#include "GameEvent.h"
#include "HudService.h"
#include "TextRenderService.h"
#include "DebrisSystem.h"
#include "ThrusterSystem.h"
#include "EditorService.h"

// ASTU/Box2D includes
#include <AstuBox2D.h>

// AST-Utilities includes
#include <AstuSuiteSDL.h>
#include <AstuInput.h>
#include <AstuECS.h>
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

// Main entry point of the application.
int main()
{
	SdlApplication app;

	// Cameras do the world-to-screen transform and used by the scene graph.
	ASTU_CREATE_AND_ADD_SERVICE(CameraService);
	ASTU_CREATE_AND_ADD_SERVICE(CameraControlService);

	// Add Services and Systems required ECS.
	ASTU_CREATE_AND_ADD_SERVICE(EntityService);
	ASTU_CREATE_AND_ADD_SERVICE(EntityFactoryService);
	ASTU_CREATE_AND_ADD_SERVICE(Box2DPhysicsSystem);
	ASTU_CREATE_AND_ADD_SERVICE(CollisionSignalService);
	ASTU_CREATE_AND_ADD_SERVICE(SceneSystem);

	// Let's add our main service that runs the application.
	ASTU_CREATE_AND_ADD_SERVICE(EntityPrototypeService, false);
	ASTU_CREATE_AND_ADD_SERVICE(GameModeService);
	ASTU_CREATE_AND_ADD_SERVICE(ShipSystem);
	ASTU_CREATE_AND_ADD_SERVICE(BulletSystem);
	ASTU_CREATE_AND_ADD_SERVICE(AsteroidSystem);
	ASTU_CREATE_AND_ADD_SERVICE(GunSystem);
	ASTU_CREATE_AND_ADD_SERVICE(WrapSystem);
	ASTU_CREATE_AND_ADD_SERVICE(AutoDestructSystem);	
	ASTU_CREATE_AND_ADD_SERVICE(HudService);	
	ASTU_CREATE_AND_ADD_SERVICE(TextRenderService);	
	ASTU_CREATE_AND_ADD_SERVICE(GameEventService);	
	ASTU_CREATE_AND_ADD_SERVICE(DebrisSystem);	
	ASTU_CREATE_AND_ADD_SERVICE(ThrusterSystem);	

	// Editor service was used to create fonts and assets.
	// ASTU_CREATE_AND_ADD_SERVICE(EditorService);
	
	// Configure physics environment.
	ASTU_SERVICE(PhysicsSystem).SetGravityVector(0, 0);

	// Configure input controls (Axis and Actions)
	auto& ims = ASTU_SERVICE(InputMappingService);
	ims.AddAxisMapping("Thrust", Keys::Up, 1.0f);
	ims.AddAxisMapping("Thrust", Keys::GamepadRightShoulder, 1.0f);
	ims.AddAxisMapping("Turn", Keys::Left, -1.0f);
	ims.AddAxisMapping("Turn", Keys::Right, 1.0f);
	ims.AddAxisMapping("Turn", Keys::GamepadLeftThumbstickX);
	ims.AddActionMapping("Fire", Keys::SpaceBar);
	ims.AddActionMapping("Fire", Keys::GamepadFaceButtonBottom);

	// Configure application.
	app.SetApplicationName("Asteroids Clone");
	app.SetVersionString("1.0.0");
	app.SetResolution(Resolution::WXGA);
	app.SetFullscreen(false);

	// Uncomment to enable/disable vertical synchronization.
	// app.SetVSync(false);

	// Uncomment to run in fullscreen full-hd resoultion
	// app.SetResolution(Resolution::FHD);
	// app.SetFullscreen(true);
	// ASTU_SERVICE(WindowService).ShowCursor(false);

	// Run the application.
	return app.Run();
} 
