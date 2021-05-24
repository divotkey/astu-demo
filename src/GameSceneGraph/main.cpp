/*
 * Example code showing how to use the 2D scene graph with SDL
 * Requires AST Utilities 0.9
 */

// C++ Standard Library includes
#include <iostream>
#include <stdexcept>

// AST Utilities includes
#include <AstUtils.h>
#include <ServiceManager.h>
#include <UpdateService.h>
#include <Events.h>
#include <SdlService.h>
#include <SdlVideoService.h>
#include <SdlEventService.h>
#include <SdlRenderService.h>
#include <SdlTimeService.h>
#include <SdlSceneGraph2.h>
#include <Camera2Service.h>
#include <EntityService.h>

// Local includes
#include "CameraModeChangerService.h"
#include "StatusIndicatorService.h"
#include "CameraControlService.h"
#include "SceneGraphTestService.h"

using namespace astu;
using namespace std;

// Constants to be adapted to the requirements of this application
const string kAppTitle = "AST Utilities, 2D Scene Graph Demo";
const string kAppVersion = "1.0.0";
const int kRes = 3;

// Global constants which should note be changed without care.
const std::array<std::array<int, 2>, 6> kResolutions = {
    800, 600,
    1024, 768, 
    1280, 720, 
    1366, 768, 
    1680, 1050, 
    1920, 1080 };


// Adds core services required for any application.
void AddCoreServices()
{
    // Get service manager instance to shorten code and avoid functions calls.
    auto & sm = ServiceManager::GetInstance();

    // The update service functions as the central facility for things 
    // (services, systems, etc) that need to be updated once within the 
    // main application loop.
    sm.AddService( make_shared<UpdateService>());

    // Receives and distributes mouse button events.
    sm.AddService( make_shared<MouseButtonEventService>() );

    // Receives and distributes mouse wheel events.
    sm.AddService( make_shared<MouseWheelEventService>() );

    // Receives and distributes keystroke events.
    sm.AddService( make_shared<KeystrokeEventService>() );

    // Receives and distributes resize events.
    sm.AddService( make_shared<ResizeEventService>() );
}

// Adds services required to run SDL-based interactive applications.
void AddSdlServices()
{
    // Get service manager instance to shorten code and avoid functions calls.
    auto & sm = ServiceManager::GetInstance();

    // Initializes and de-initializes SDL and its subsystems.
    sm.AddService( make_shared<SdlService>() );

    // Maintains main application window.
    sm.AddService( make_shared<SdlVideoService>() );

    // Offers an layer-based 2D graphics facility based on SDL render mechanism.
    sm.AddService( make_shared<SdlRenderService>() );

    // Empties the SDL-Event queue and distributes events.
    sm.AddService( make_shared<SdlEventService>() );

    // Provides an SDL-based implementation of the ITimeService interface.
    sm.AddService( make_shared<SdlTimeService>() );
}

// Adds application specific services.
void AddCustomServices()
{
    // We are using the ASTU_CREATE_AND_ADD_SERVICE macro here instead
    // the usual way to create and add services. There is no difference
    // to the way services gete added in e.g., AddSdlServices()
    // or AddCoreServices().
    //
    // In case services must be created with a parameter in the constructor,
    // the macro ASTU_CREATE_AND_ADD_SERVICE cannot be used.
    //
    // Example hot to add services without macros:
    // auto & sm = ServiceManager::GetInstance();
    // sm.AddService( make_shared<Camera2Service>() );

    // We are using the camera system to become independent from the
    // actual screen resolution and sill beeing able to see th entire 
    // game world. Beside that we need the camera to carry out a 
    // screen-to-world transformation to place graphical elements via 
    // mouse click.
    ASTU_CREATE_AND_ADD_SERVICE( Camera2Service );

    // The SDL vertex buffer builder is used to create vertex buffer that
    // work with the SDL-based implementation of the scene graph.
    ASTU_CREATE_AND_ADD_SERVICE( SdlVertexBuffer2BuilderService );

    // This service provides an SDL-based implementation of the 2D
    // scene graph.
    ASTU_CREATE_AND_ADD_SERVICE( SdlSceneGraph2 );

    // This application's own service, which is used to add create and
    // some leafes and branches to the scene graph.
    ASTU_CREATE_AND_ADD_SERVICE( SceneGraphTestService );

    // Add service to let the user change the camera mode.
    ASTU_CREATE_AND_ADD_SERVICE( CameraModeChangerService );

    // Add signal service for string, to show status updates.
    ASTU_CREATE_AND_ADD_SERVICE( SignalService<std::string> );

    // Add service that reacts to string status messages. */
    ASTU_CREATE_AND_ADD_SERVICE( StatusIndicatorService );

    // Add service which let the user controll the camera with the mouse. */
    ASTU_CREATE_AND_ADD_SERVICE( CameraControlService );    
}


// Output some information about this application.
void PrintHeader()
{
    cout << kAppTitle << " - Version " << kAppVersion << endl << endl;
    SayVersion();
    SayCopyright(true);
}

// Configures services according to application specific settings and configurations.
void ConfigureApplication()
{
    // Configure application main window.
    auto & wm = ASTU_SERVICE(IWindowManager);

    // wm.SetTitle(kAppTitle + " - Version " + kAppVersion);
    wm.SetSize(kResolutions.at(kRes)[0], kResolutions.at(kRes)[1]);
    wm.SetResizeable(true);

    ASTU_SERVICE(StatusIndicatorService)
        .SetWindowTitle(kAppTitle + " - Version " + kAppVersion);

    // /** Configure the game world to be 4 by 3 meters. */
    // ASTU_SERVICE(SceneGraphTestService).SetWorldSize(4, 3);

    // ASTU_SERVICE(CameraModeChangerService)
    //     .SetFixedWorldWidth(5)
    //     .SetFixedWorldHeight(4);
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