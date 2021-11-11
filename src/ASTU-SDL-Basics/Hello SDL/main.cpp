/** 
 * Example Application: AST-Utilities + SDL Hello world
 * @file main.cpp
 * @version 1.0.0
 * @author Roman Divotkey
 * @copyright MIT License
 */

// AST-Utilities includes
#include <AstUtils.h>

void ReportError()
{
    SayText("An error has occurred: ", false);
    SayText(GetLastErrorMessage());
    SayText(GetErrorDetails());
}

int main()
{
    SayVersion();
    SayCopyright(true);

    if (InitApp(1366, 768) != NO_ERROR) {
        ReportError();
        return -1;
    }

    SetWindowTitle("Hello AST/SDL World");
    while(!IsAppTerminated()) {
        ClearCanvas();
        UpdateApp();
    }

    QuitApp();
    return 0;
}