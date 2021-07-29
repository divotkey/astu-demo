// Local includes
#include "MainService.h"

// AST-Utilities includes
#include <AstuSuite2D.h>

using namespace astu::suite2d;
using namespace astu;

MainService::MainService()
    : BaseService("Main Service")
{
    // Intentionally left empty.
}

void MainService::OnStartup()
{
    // We would like to draw a triangle. This means we need to create a new
    // scene graph element and add it to the scene graph. The scene graph
    // element is supposed to draw something, so it is a leaf element and, in
    // our case, a polyline element. The polyline requires the vertices of the
    // geometry to be drawn as a VertexBuffer.    
    //    
    // If it is unclear what is happening, take a look at Scene Graph Demo 1.
    // 
    // Unlike Scene Graph Demo1, here, we use the builder classes to configure
    // the scene graph. This allows us to add a triangle with a single (long)
    // line of code without allowing local variables back. Admittedly, the line
    // of code is quite long, but we format it accordingly to compensate.

    // Add a polyline element containing the triangle vertices to.
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(PolylineBuilder()
        .Name("Triangle")
        .Color(RalColors::TrafficRed)
        .Translation(150, 150)
        .VertexBuffer( ShapeGenerator().GenTriangle(100) )
        .Build()
    );

    // Because adding elements becomes easier now, let's add additional things.

    // Add a star...
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(PolylineBuilder()
        .Name("Star")
        .Color(RalColors::TrafficBlue)
        .Translation(400, 150)
        .VertexBuffer( ShapeGenerator().GenStar(70) )
        .Build()
    );

    // And a cross...
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(PolylineBuilder()
        .Name("Cross")
        .Color(RalColors::TrafficGreen)
        .Translation(650, 150)
        .VertexBuffer( ShapeGenerator().GenCross(100) )
        .Build()
    );

    // And a circle...
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(PolylineBuilder()
        .Name("Circle")
        .Color(RalColors::TrafficYellow)
        .Translation(850, 150)
        .VertexBuffer( ShapeGenerator().GenCircle(70) )
        .Build()
    );
}

void MainService::OnShutdown()
{
    // Cleanup
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachAll();
}