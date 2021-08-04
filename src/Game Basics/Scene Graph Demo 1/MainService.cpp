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
    
    // Create triangle vertices using the convenient shape generator.
    std::shared_ptr<VertexBuffer2f> vertices = ShapeGenerator().GenTriangleVb(100);

    // Create and initialize a new polyline scene graph element.
    std::shared_ptr<Polyline> poly = std::make_shared<Polyline>(vertices);
    poly->SetName("Triangle");
    poly->SetColor(RalColors::TrafficWhite);
    poly->SetLocalTransform(Transform2f().SetTranslation(100, 100));

    // Add the polyline element to the scene graph.
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(poly);
}

void MainService::OnShutdown()
{
    // Cleanup
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachAll();

    // Alternatively we could only remove the nodes we have added.
    // ASTU_SERVICE(SceneGraph).GetRoot()->DetachChild("Triangle");
}