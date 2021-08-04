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
    GetCamera().ShowFitting(16, 9);
    InitSceneGraphElements();
}

void MainService::OnShutdown()
{
    // Cleanup
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachAll();
}

void MainService::OnUpdate()
{    
    // Rotate pivot node.
    Transform2f tx = pivotNode->GetLocalTransform();
    tx.Rotate(-SPEED * GetElapsedTimeF());
    pivotNode->SetLocalTransform(tx);
}

void MainService::InitSceneGraphElements()
{
    shared_ptr<VertexBuffer2f> triangleShape = ShapeGenerator().GenTriangleVb(0.5f);

    auto centerNode = NodeBuilder()
        .Name("Center")
        .Build();

    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(centerNode);

    pivotNode = NodeBuilder()
        .Name("Pivot")
        .Build();

    centerNode->AttachChild(CreateWorldOutline());
    centerNode->AttachChild(pivotNode);
    
    centerNode->AttachChild(PolylineBuilder()
        .Name("Center Cross")
        .Color(RalColors::TrafficRed)
        .VertexBuffer( ShapeGenerator().GenCross(0.25f) )
        .Build()
        );

    pivotNode->AttachChild(PolylineBuilder()
        .Name("Triangle")
        .Color(RalColors::TrafficYellow)
        .Translation(1.5f, 0.0f)
        .VertexBuffer( triangleShape )
        .Build()
        );

    pivotNode->AttachChild(PolylineBuilder()
        .Name("Triangle")
        .Color(RalColors::TrafficGreen)
        .Translation(-1.5f, 0.0f)
        .RotationDeg(180)
        .VertexBuffer( triangleShape )
        .Build()
        );
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