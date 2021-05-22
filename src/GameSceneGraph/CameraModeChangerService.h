#pragma once

// C++ Standard Libraries
#include <string>

// AST Utilities includes
#include <Events.h>
#include <Camera2Service.h>

// This service lets the user change the camera mode while the application 
// is running.

class CameraModeChangerService 
    : public astu::BaseService
    , public astu::KeystrokeListener
    , public astu::Camera2Client
{
public:

    /**
     * Constructor.
     */
    CameraModeChangerService();

    /**
     * Specifies the dimenions of the visible game world
     * 
     * @param w the width of the visible area in world units
     * @param h the height of the visible area in world units
     */
    CameraModeChangerService& SetViewSize(float w, float h);

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via KeystrokeListener
    virtual bool OnKeyPressed(int keycode);

private:
    enum Mode {Screen, FixedWidth, FixedHeight, Fitting, Filling, Streched};

    Mode mode;
    int switchKey;
    float viewWidth;
    float viewHeight;

    void UpdateCameraMode();
    void UpdateStatus(const std::string & msg);
};