/** 
 * Example Application: 2D Scene Graph Demo #3
 * 
 * @file main.cpp
 * @version 1.0.0
 * @author Roman Divotkey
 * @copyright MIT License
 */

// Local includes
#include "MainService.h"

// AST Utilities includes
#include <AstuSuiteSDL.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>

// C++ Standard Library includes
#include <iostream>
#include <stdexcept>

using namespace astu2d;
using namespace astu;
using namespace std;

// Main entry point of the application.
int main()
{
    SdlApplication app;
    app.SetApplicationName("AST-Utilities, Entity Demo #1");
    app.SetVersionString("1.0.0");

    // Cameras do the world-to-screen transform and used by the scene graph.
    ASTU_CREATE_AND_ADD_SERVICE(CameraService);
    ASTU_CREATE_AND_ADD_SERVICE(CameraControlService);

    // Add Services and Systems required ECS.
    ASTU_CREATE_AND_ADD_SERVICE(EntityService);
    ASTU_CREATE_AND_ADD_SERVICE(AutoRotateSystem);
    ASTU_CREATE_AND_ADD_SERVICE(SceneSystem);

    // Let's add our main service that runs the application.
    ASTU_CREATE_AND_ADD_SERVICE(MainService);

    // Run the application.
    try {
        app.Run();
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