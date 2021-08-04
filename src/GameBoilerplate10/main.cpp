/*
 * Boilerplate Code for SDL/ASTU Applications
 * Requires AST Utilities 0.10
 */

// AST-Utilities includes
#include <AstuSuiteSDL.h>

using namespace astu;

// Main entry point of the application.
int main()
{
    SdlApplication app;

    app.SetApplicationName("Boilerplate Code für SDL/ASTU Applications");
    app.SetVersionString("1.0.0");
    return app.Run(); 
} 