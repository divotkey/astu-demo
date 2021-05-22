// C++ Standard Library includes
#include <stdexcept>

// AST Utilities includes
#include <IWindowManager.h>

// Local includes
#include "Mouse.h"
#include "Scene2.h"
#include "VertexBuffer2.h"
#include "Shape2Generator.h"
#include "SceneGraphTestService.h"

using namespace astu;
using namespace std;

SceneGraphTestService::SceneGraphTestService()
    : Service("Scene Graph2D Test Service")
    , worldSize(0, 0)
    , markerColor(WebColors::Gray)
    , mouseButton(Mouse::Button::LEFT)
{
    // Intentionally left empty.
}

void SceneGraphTestService::SetWorldSize(float w, float h)
{
    if (w < 0 || h < 0) {
        throw std::domain_error(
            "Dimensions of world size must be greater or equal zero");
    }
    worldSize.Set(w, h);
}

void SceneGraphTestService::OnStartup()
{
    // Use screen size as world size as fallback dimensions of the world.
    if (worldSize.x <= 0 || worldSize.y <= 0)  {
        auto & wnd = ASTU_SERVICE( IWindowManager );
        worldSize.x = static_cast<float>(wnd.GetWidth());
        worldSize.y = static_cast<float>(wnd.GetHeight());
    }

    MarkWorldDimensions();
    CreateVertexBuffersAndColors();
    curShape = curColor = 0;
}

void SceneGraphTestService::OnShutdown()
{
    // Intentionally left empty.
}

bool SceneGraphTestService::OnMouseButtonPressed(int button, int x, int y)
{
    if (button != mouseButton) {
        return false;
    }    

    // Transform screen coordinates to world coordinates.
    Vector2f worldPoint = GetCamera()
        .GetInverseMatrix()
        .TransformPoint(static_cast<float>(x), static_cast<float>(y));

    // Add a new object to the scene graph.
    AddTestObject(worldPoint);

    return true;
}

void SceneGraphTestService::CreateVertexBuffersAndColors()
{
    // Make the objects ca. 2% of the average world size dimensions.
    const float size = 0.05f * (worldSize.x + worldSize.y) / 2;

    Shape2Generator generator;
    objectShapes.push_back( generator.GenStar(size / 2) );
    objectShapes.push_back( generator.GenCross(size) );
    objectShapes.push_back( generator.GenArrow(size) );

    objectColors.push_back(WebColors::Orange);
    objectColors.push_back(WebColors::Green);
    objectColors.push_back(WebColors::Purple);
    objectColors.push_back(WebColors::Blue);
    objectColors.push_back(WebColors::Red);
    objectColors.push_back(WebColors::Lime);
}

void SceneGraphTestService::AddTestObject(const astu::Vector2f p)
{
    ASTU_SERVICE(SceneGraph2)
        .GetRoot()->AttachChild(Polyline2Builder()
        .Color(objectColors[curColor++])
        .Translation(p)
        .VertexBuffer(objectShapes[curShape++])
        .Build());

    if (curShape >= objectShapes.size()) {
        curShape = 0;
    }

    if (curColor >= objectColors.size()) {
        curColor = 0;
    }
}

void SceneGraphTestService::MarkWorldDimensions()
{
    // The idea is to create some visual hints that show the dimensions of the
    // game world. We should make the world size we use a tiny bit smaller than
    // the actual size so that the visual hints are visible and not hidden on
    // the edge of the screen.

    const float width = worldSize.x - (worldSize.x + worldSize.y) * 0.005f;
    const float height = worldSize.y - (worldSize.x + worldSize.y) * 0.005f;

    // Make the corner markes ca. 2% of the average world size dimensions.
    const float cs = 0.02f * (width + height) * 0.5f;

    // Generate and resuse the vertex buffer for visualizing the corners points.
    auto cornerVb = Shape2Generator().GenSquare(cs);

    // For the sake of readability let's use some contants.
    const float left = -width / 2;
    const float right = width / 2;
    const float top = -height / 2;
    const float bottom = height / 2;

    // Create scene graph branch using buidlers and method chaining.
    // Builders and method chaining (combined fluent builders) might reduce
    // readability a bit (at least for inexperienced developers), but
    // increasing the development speed reduces the time needed to
    // write the code. 
    auto branch = Node2Builder()
        .Name("WORLD_BOUNDARIES")
        // Add Maineframe
        .AttachChild(Polyline2Builder()
            .Name("WORLD_FRAME")
            .Color(markerColor)
            .VertexBuffer(Shape2Generator()
                .GenRectangle(width, height))
            .Build())
        // Add center marker
        .AttachChild(Polyline2Builder()
            .Name("CENTER")
            .Color(markerColor)
            .Translation(0, 0)
            .VertexBuffer(Shape2Generator().GenCross(cs))
            .Build())
        // Add upper left corner maker
        .AttachChild(Polyline2Builder()
            .Name("UPPER_LEFT")
            .Color(markerColor)
            .Translation(left + cs / 2, top + cs / 2)
            .VertexBuffer(cornerVb)
            .Build())
        // Add upper right corner maker
        .AttachChild(Polyline2Builder()
            .Name("UPPER_RIGHT")
            .Color(markerColor)
            .Translation(right - cs / 2, top + cs / 2)
            .VertexBuffer(cornerVb)
            .Build())
        // Add lower left corner maker
        .AttachChild(Polyline2Builder()
            .Name("LOWER_LEFT")
            .Color(markerColor)
            .Translation(left + cs / 2, bottom - cs / 2)
            .VertexBuffer(cornerVb)
            .Build())
        // Add lower right corner maker
        .AttachChild(Polyline2Builder()
            .Name("LOWER_RIGHT")
            .Color(markerColor)
            .Translation(right - cs / 2, bottom - cs / 2)
            .VertexBuffer(cornerVb)
            .Build())
        // Add top center marker
        .AttachChild(Polyline2Builder()
            .Name("TOP_CENTER")
            .Color(markerColor)
            .Translation(0, top + cs / 2)
            .VertexBuffer(cornerVb)
            .Build())
        // Add bottom center marker
        .AttachChild(Polyline2Builder()
            .Name("BOTTOM_CENTER")
            .Color(markerColor)
            .Translation(0, bottom - cs / 2)
            .VertexBuffer(cornerVb)
            .Build())
        // Add left center marker
        .AttachChild(Polyline2Builder()
            .Name("LEFT_CENTER")
            .Color(markerColor)
            .Translation(left + cs / 2, 0)
            .VertexBuffer(cornerVb)
            .Build())
        // Add right center marker
        .AttachChild(Polyline2Builder()
            .Name("RIGHT_CENTER")
            .Color(markerColor)
            .Translation(right - cs / 2, 0)
            .VertexBuffer(cornerVb)
            .Build())
        .Build();

    // Add branch.
    ASTU_SERVICE(SceneGraph2).GetRoot()->AttachChild(branch);
}

