/** 
 * Example Application: Camera Demo
 * 
 * @file main.cpp
 * @version 1.0.0
 * @author Roman Divotkey
 * @copyright MIT License
 */

// Local includes
#include "MainService.h"

// AST Utilities includes
#include <AstuSuite2D.h>
#include <AstuSuiteSDL.h>

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
    app.SetApplicationName("AST-Utilities, Camera Demo");
    app.SetVersionString("1.0.0");
    app.SetResizable(true);
    app.SetWindowTitle(app.GetApplicationName() 
        + ": Use right mouse button to move the camera");

    // With a camera service, we can use cameras that do the world-to-screen
    // transformation for us.
    ASTU_CREATE_AND_ADD_SERVICE(CameraService);

    // Adding the camera control service, let's us move and zoom the camera
    // with the mouse.
    ASTU_CREATE_AND_ADD_SERVICE(CameraControlService);

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