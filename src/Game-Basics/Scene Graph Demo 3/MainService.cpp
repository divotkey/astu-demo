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
    // We will create two scene nodes that draw an identical triangle, so we
    // can use the vertex data for both nodes to save some memory.   
    shared_ptr<VertexBuffer2f> triangleShape = ShapeGenerator().GenTriangleVb(50);

    // We create a node that is placed exactly in the center of the screen and
    // can contain other child nodes. It will be the only node we add to the
    // scene graph. All other nodes will be child nodes of this node.
    auto centerNode = NodeBuilder()
        .Name("Center")
        .Translation( GetCenter() )
        .Build();

    // We can also add this node to the scene graph right away. We could also
    // do this later. It doesn't matter when a scene node is added because
    // rendering is done later by the scene graph during the render cycle .
    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(centerNode);

    // We now create the node that we will later rotate around its center point.
    // All child nodes added to this node will rotate relative to this node.
    pivotNode = NodeBuilder()
        .Name("Pivot")
        .Build();

    // We also need to add this node indirectly to the scene graph by making it
    // a child node of the center node.
    centerNode->AttachChild(pivotNode);

    // Let's add a cross in the middle of the rotation elements.
    // Depending on whether we want the center cross to rotate or not, we need
    // to add it to the pivot node or to the center node. In this case, we
    // decide that we do not want the cross to rotate and we add it to the
    // center node.
    centerNode->AttachChild(PolylineBuilder()
        .Name("Center Cross")
        .Color(RalColors::TrafficRed)
        .VertexBuffer( ShapeGenerator().GenCross(25) )
        .Build()
        );

    // And now we add two triangles, each left and right of the center.
    // Note that all child nodes must be positioned relative to the parent node.

    // The right triangle.
    pivotNode->AttachChild(PolylineBuilder()
        .Name("Triangle")
        .Color(RalColors::TrafficYellow)
        .Translation(150, 0)
        .VertexBuffer( triangleShape )
        .Build()
        );

    // The left triangle.
    pivotNode->AttachChild(PolylineBuilder()
        .Name("Triangle")
        .Color(RalColors::TrafficGreen)
        .Translation(-150, 0)
        .RotationDeg(180)
        .VertexBuffer( triangleShape )
        .Build()
        );
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

Vector2f MainService::GetCenter()
{
    auto& winSrv = ASTU_SERVICE(WindowService);
    return Vector2f((float) winSrv.GetWidth() / 2, (float) winSrv.GetHeight() / 2);
}
