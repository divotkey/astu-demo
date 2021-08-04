// Local includes
#include "MainService.h"

// AST-Utilities includes
#include <AstuSuite2D.h>

using namespace astu::suite2d;
using namespace astu;
using namespace std;

#define SPEED   1.0f

MainService::MainService()
    : BaseService("Main Service")
{
    // Intentionally left empty.
}

void MainService::OnStartup()
{
    // Configure the default camera to show 16 by 9 meters of the game world.
    GetCamera().ShowFitting(16, 9);

    // Add markers to visualize the outline of the game world.
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild( CreateWorldOutline() );

    // Add some game entities.
    AddEntity(0, 0, 0);
    AddEntity(-5, -3, -1.0f);
    AddEntity(5, -3, 2.5f);
    AddEntity(0, 3, -5.0f);
}

void MainService::OnShutdown()
{
    // Cleanup things we added directly to the scene graph.
    // Note: Scene graph elements added via entities will be removed
    // automatically by the SceneSystem.
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachAll();
}

void MainService::AddEntity(float x, float y, float av)
{
    shared_ptr<Entity> entity = make_shared<Entity>();
    entity->AddComponent( make_shared<CPose>(x, y));
    entity->AddComponent( make_shared<CScene>(PolylineBuilder()
        .Color(RalColors::TrafficWhite)
        .VertexBuffer(ShapeGenerator().GenTriangle(0.5f))
        .Build())
    );

    entity->AddComponent( make_shared<CAutoRotate>(av) );

    ASTU_SERVICE(EntityService).AddEntity(entity);
}

shared_ptr<Spatial> MainService::CreateWorldOutline()
{
    const float width = GetCamera().GetViewWidth() * 0.99f;
    const float height = GetCamera().GetViewHeight() * 0.99f;
    const float rectSize = 0.25f;
    const float left = -width / 2 + rectSize / 2;
    const float right = width / 2 - rectSize / 2;
    const float bottom = height / 2 - rectSize / 2;
    const float top = -height / 2 + rectSize / 2;
    const Color4f mainColor = RalColors::TrafficGreyA;
    const Color4f secondaryColor = RalColors::TrafficGreyB;

    return NodeBuilder()
        .Name("WorldOutline")
        // Left marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(left, 0)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Right marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(right, 0)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Bottom marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(0, height / 2 - rectSize / 2)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Top marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(0, top)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Upper left marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(left, top)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Upper right marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(right, top)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Bottom left marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(left, bottom)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        // Bottom right marker
        .AttachChild(PolylineBuilder()
            .Color(secondaryColor)
            .Translation(right, bottom)
            .VertexBuffer( ShapeGenerator().GenRectangle(rectSize, rectSize))
            .Build())
        //Outer frame
        .AttachChild(PolylineBuilder()
            .Color(mainColor)
            .VertexBuffer( ShapeGenerator().GenRectangle(width, height))
            .Build())
        .Build();        
}