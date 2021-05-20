/*
 * Boilerplate Code for SDL/ASTU Applications - Version 1.2.0
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

using namespace astu;
using namespace std;

// Constants to be adapted to the requirements of this application
const string kAppTitle = "Boilerplate Code for SDL/ASTU Applications";
const string kAppVersion = "1.3.0";
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
    // Get service manager instance to shorten code and avoid functions calls.
    auto & sm = ServiceManager::GetInstance();

    // TODO add custom services.
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
    // Get service manager instance to shorten code and avoid functions calls.
    auto & sm = ServiceManager::GetInstance();

    // Configure application main window.
    auto & wm = ASTU_SERVICE(IWindowManager);
    wm.SetTitle(kAppTitle + " - Version " + kAppVersion);
    wm.SetSize(kResolutions.at(kRes)[0], kResolutions.at(kRes)[1]);
}

// Starts all services, runs the main loop and shuts down all services.
void RunApplication()
{
    // Get service manager instance to shorten code and avoid functions calls.
    auto & sm = ServiceManager::GetInstance();

    // Starts all services.
    sm.StartupAll();

    // Get references to update service to update once within the game loop.
	auto & updater = ASTU_SERVICE(UpdateService);

    // Get references to event service to query whether the user wants to terminate
    // the application.
	auto & event = ASTU_SERVICE(SdlEventService);

    // Run the main loop until user wants to germinate.
	while ( !event.IsQuit() )
	{
		updater.UpdateAll();
	}

    // Shuts all services down.
    sm.ShutdownAll();
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