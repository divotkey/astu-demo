#pragma once

// C++ Standard Libraries
#include <string>

// AST Utilities includes
#include <Camera2Service.h>
#include <UpdateService.h>
#include <Vector2.h>
#include <Events.h>

// This service lets the user change the camera mode while the application 
// is running.

class CameraControlService 
    : public astu::BaseService
    , public astu::Updatable
    , public astu::KeystrokeListener
    , public astu::MouseButtonListener
    , public astu::MouseWheelListener
    , public astu::Camera2Client
{
public:

    /**
     * Constructor.
     * 
     * @param updatePriority the priority used to update this service
     */
    CameraControlService(int updatePriority = astu::Priority::Normal);

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via IUpdatable
    virtual void OnUpdate() override;

    // Inherited via KeystrokeListener
    virtual bool OnKeyPressed(int keycode);

    // Inherited via MouseButtonListener
    virtual bool OnMouseButtonPressed(int button, int x, int y) override;
    virtual bool OnMouseButtonReleased(int button, int x, int y) override;

    // Inherited via MouseWheelListener
    virtual bool OnMouseWheel(int amount) override;


private:
    /** The mouse button used to control the camera position. */
    int mouseButton;
    
    /** The key used to center the camera. */
    int homeKey;

    /** Indicates whether the user is currently changing the camera position. */
    bool dragging;

    /** Used to calculate the zoom factor. */
    int zoomLevel;

    /** The start position of the camera movement in screen coordinates. */
    astu::Vector2f startScreenPos;

    /** The start position of the camera movement in world coordinates. */
    astu::Vector2f startWorldPos;

    void UpdateCamera(int screenX, int screenY);


};