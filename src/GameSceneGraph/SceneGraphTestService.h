#pragma once

// AST Utilities includes
#include <CameraService2D.h>
#include <VertexBuffer2D.h>
#include <Vector2.h>
#include <Service.h>
#include <Events.h>
#include <Color.h>

// C++ Standard Libray includes
#include <memory>
#include <vector>


// This service will add some graphical elements to the scene graph
// on startup.
class SceneGraphTestService 
    : public astu::BaseService
    , public astu::MouseButtonListener
    , public astu::CameraClient2D
{
public:

    SceneGraphTestService();

    /**
     * Sets the size of the game world.
     * 
     * @param w the width of the world in world units.
     * @param h the height of the world in world units.
     */
    void SetWorldSize(float w, float h);

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via MouseButtonListener
    virtual bool OnMouseButtonPressed(int button, int x, int y) override;

private:
    /** The size of the game world in world units. */
    astu::Vector2f worldSize;

    /** The color used for frame and marker. */
    astu::Color4f markerColor;

    /** List with vertex buffer used to add objects by mouse click. */
    std::vector<std::shared_ptr<astu::VertexBuffer2D>> objectShapes;

    /** List with colors used to add objects by mouse click. */
    std::vector<astu::Color4f> objectColors;

    /** The mouse button used to add scene graph objects. */
    int mouseButton;

    /** Index pointing at the current shape to used for adding objects. */
    size_t curShape;
    
    /** Index pointing at the current color to used for adding objects. */
    size_t curColor;

    /**
     * Creates a branch in the scene graph, to visualize the world dimeneions.
     */
    void MarkWorldDimensions();

    /**
     * Creates the vertex buffers and list of colors.
     * 
     * The vertex buffer and colors are used to for objects that get added
     * to the scene graph by mouse clicks.
     */
    void CreateVertexBuffersAndColors();

    /**
     * Adds a test Object to the scene graph.
     * 
     * @param p the position where to add the object in world space
     */
    void AddTestObject(const astu::Vector2f p);

};