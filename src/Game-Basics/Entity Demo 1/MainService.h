#pragma once

// AST Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>

class MainService 
    : public astu::BaseService
    , private astu2d::CameraClient
{
public:
    
    /** Constructor. */
    MainService();

private:
    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    /**
     * Adds a game entity to the world.
     * 
     * @param x     the the x-coordinate of the entity spawn location
     * @param y     the the y-coordinate of the entity spawn location
     * @param av    the rotation speed of the entity in radians per second
     **/
    void AddEntity(float x, float y, float av);

    /** Creates scene elements that visualizes the outline of the game world. */
    std::shared_ptr<astu2d::Spatial> CreateWorldOutline();
};