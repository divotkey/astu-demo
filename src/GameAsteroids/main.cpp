/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// C++ Standard Library includes
#include <iostream>
#include <stdexcept>

// AST Utilities includes
#include <AstUtils.h>
#include <ServiceManager.h>
#include <UpdateService.h>
#include <SdlService.h>
#include <SdlVideoService.h>
#include <SdlEventService.h>
#include <SdlRenderService.h>
#include <SdlTimeService.h>
#include <IRenderService.h>
#include <IWindowManager.h>
#include <Events.h>

#include <EntityFactoryService.h>
#include <SdlSceneGraph2.h>
#include <Camera2Service.h>
#include <EntityService.h>

// Local includes
#include "PhysicsSystem.h"
#include "Mesh2System.h"
#include "ShipSystem.h"
#include "WrapSystem.h"
#include "GunSystem.h"
#include "BulletSystem.h"
#include "GameManager.h"

using namespace astu;
using namespace std;


// Constants to be adapted to the requirements of this application
const string kAppTitle = "Asteroids Clone";
const string kAppVersion = "1.0.0";
const Color4f backgroundColor = WebColors::Silver;

// Change this value to let the application window have one of the 
// standard dimentions specified in the kResolutions array.
const int kRes = 3;

// Global constants which should note be changed without care.
const std::array<std::array<int, 2>, 6> kResolutions = {
    800, 600,       // res 0    SVGA,       Aspect ratio 4:3
    1024, 768,      // res 1    XGA,        Aspect ratio 4:3 
    1280, 720,      // res 2    HD (921k)   Aspect Ratio ~16:9 
    1366, 768,      // res 3    HD (1049k)  Aspect Ratio ~16:9 
    1680, 1050,     // rew 4    WSXGA+      Aspect Ratio 16:9
    1920, 1080      // res 5    FHD (1080)  Aspect Ratio 16:9
    };   


// Concatenates some meta-information about the application to assemble a title.
std::string GetApplicationTitle() {
    return kAppTitle + " - Version " + kAppVersion;
}

// Output some information about this application.
void PrintHeader()
{
    cout << GetApplicationTitle << endl << endl;
    SayVersion();
    SayCopyright(true);
}

// Adds core services required for any application.
void AddCoreServices()
{
    // The update service functions as the central facility for things 
    // (services, systems, etc) that need to be updated once within the 
    // main application loop.
    ASTU_CREATE_AND_ADD_SERVICE( UpdateService );

    // Receives and distributes mouse button events.
    ASTU_CREATE_AND_ADD_SERVICE( MouseButtonEventService );

    // Receives and distributes mouse wheel events.
    ASTU_CREATE_AND_ADD_SERVICE( MouseWheelEventService );

    // Receives and distributes mouse move events.
    ASTU_CREATE_AND_ADD_SERVICE( MouseMoveEventService );

    // Receives and distributes keystroke events.
    ASTU_CREATE_AND_ADD_SERVICE( KeystrokeEventService );

    // Receives and distributes resize events.
    ASTU_CREATE_AND_ADD_SERVICE( ResizeEventService );
}

// Adds services required to run SDL-based interactive applications.
void AddSdlServices()
{
    // Initializes and de-initializes SDL and its subsystems.
    ASTU_CREATE_AND_ADD_SERVICE( SdlService );

    // Maintains main application window.
    ASTU_CREATE_AND_ADD_SERVICE( SdlVideoService );

    // Offers an layer-based 2D graphics facility based on SDL render mechanism.
    ASTU_CREATE_AND_ADD_SERVICE( SdlRenderService );

    // Empties the SDL-Event queue and distributes events.
    ASTU_CREATE_AND_ADD_SERVICE( SdlEventService );

    // Provides an SDL-based implementation of the ITimeService interface.
    ASTU_CREATE_AND_ADD_SERVICE( SdlTimeService );
}

// Adds application specific services.
void AddCustomServices()
{
    ASTU_CREATE_AND_ADD_SERVICE( Camera2Service );
    ASTU_CREATE_AND_ADD_SERVICE( SdlSceneGraph2 );
    ASTU_CREATE_AND_ADD_SERVICE( SdlVertexBuffer2BuilderService );
    ASTU_CREATE_AND_ADD_SERVICE( EntityService );
    ASTU_CREATE_AND_ADD_SERVICE( EntityFactoryService );
    ASTU_CREATE_AND_ADD_SERVICE( Mesh2System );    
    ASTU_CREATE_AND_ADD_SERVICE( PhysicsSystem );
    ASTU_CREATE_AND_ADD_SERVICE( ShipSystem );
    ASTU_CREATE_AND_ADD_SERVICE( WrapSystem );
    ASTU_CREATE_AND_ADD_SERVICE( GameManager );
    ASTU_CREATE_AND_ADD_SERVICE( GunSystem );
    ASTU_CREATE_AND_ADD_SERVICE( BulletSystem );
}

// Configures services according to application specific settings and configurations.
void ConfigureApplication()
{
    // Configure application main window.
    auto & wm = ASTU_SERVICE(IWindowManager);
    wm.SetTitle(kAppTitle + " - Version " + kAppVersion);
    wm.SetSize(kResolutions.at(kRes)[0], kResolutions.at(kRes)[1]);

    // Configure background color
    ASTU_SERVICE(IRenderService).SetBackgroundColor(backgroundColor);
}

// Starts all services, runs the main loop and shuts down all services.
void RunApplication()
{
    // This marco fetchtes an instance of the service manager and starts up
    // all services.
    ASTU_STARTUP_SERVICES();

    // Get references to update service to update once within the game loop.
	auto & updater = ASTU_SERVICE(UpdateService);

    // Get references to event service to query whether the user wants
    // to terminate the application.
	auto & event = ASTU_SERVICE(SdlEventService);

    // Run the main loop until user wants to terminate the application.
	while ( !event.IsQuit() )
	{
		updater.UpdateAll();
	}

    // This marco fetchtes an instance of the service manager and shuts down
    // all services.
    ASTU_SHUTDOWN_SERVICES();
}

// Main entry point of the application.
int main()
{
    PrintHeader();

    try {
        AddCoreServices();
        AddSdlServices();
        AddCustomServices();

        ConfigureApplication();
        RunApplication();
    }
    catch (const runtime_error & e) {
        cerr << e.what() << endl;
        return -1;
    }
    catch (const logic_error & e) {
        cerr << "programmer error: " << e.what() << endl;
        return -1;
    }

    return 0;
} 