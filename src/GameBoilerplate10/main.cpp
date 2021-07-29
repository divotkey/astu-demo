/*
 * Boilerplate Code for SDL/ASTU Applications
 * Requires AST Utilities 0.10
 */

// AST Utilities includes
#include <AstuSuiteSDL.h>

// C++ Standard Library includes
#include <iostream>
#include <stdexcept>

using namespace astu;
using namespace std;

// Main entry point of the application.
int main()
{
    SdlApplication app;

    app.SetApplicationName("Boilerplate Code für SDL/ASTU Applications");
    app.SetVersionString("1.0.0");
 
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