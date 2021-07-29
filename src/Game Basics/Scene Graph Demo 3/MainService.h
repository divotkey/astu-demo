#pragma once

// AST Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>

class MainService 
    : public astu::BaseService
    , private astu::Updatable
    , private astu::TimeClient
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
    virtual void OnUpdate () override;    

    /**
     * Returns the current center of the screen.
     * 
     * @return the center of the screen in screen coordinates
     */
    astu::Vector2f GetCenter();
};