#pragma once

// AST Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>

class MainService 
    : public astu::BaseService
    , private astu::Updatable
    , private astu::TimeClient
    , private astu2d::LineRendererClient2f
    , private astu2d::CameraClient
{
public:
    
    /** Constructor. */
    MainService();

private:
    /** The node to be rotated by this service. */
    std::shared_ptr<astu2d::Node> pivotNode;

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via Updatable
    virtual void OnUpdate() override;

    /** Creates our demo-scene graph elements. */
    void InitSceneGraphElements();

    /** Creates scene elements that visualizes the outline of the game world. */
    std::shared_ptr<astu2d::Spatial> CreateWorldOutline();
};