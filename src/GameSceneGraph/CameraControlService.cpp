// C++ Standard Library includes
#include <iostream>

// AST Utilities includes
#include <Mouse.h>
#include <Events.h>
#include <Keyboard.h>

// Local includes
#include "CameraControlService.h"

using namespace astu;
using namespace std;

CameraControlService::CameraControlService(int updatePriority)
    : Service("Camera Control Service")
    , Updatable(updatePriority)
    , mouseButton(Mouse::Button::RIGHT)
    , homeKey(Keyboard::KEY_HOME)
{
    // Intentionally left empty.
}

void CameraControlService::OnStartup()
{
    dragging = false;
}

void CameraControlService::OnShutdown()
{
    // Intentionally left empty.
}

void CameraControlService::OnUpdate()
{
    if (!dragging) {
        return;
    }

    Mouse mouse;
    UpdateCamera(mouse.GetCursorX(), mouse.GetCursorY());
}

bool CameraControlService::OnKeyPressed(int keycode)
{
    if (keycode == homeKey) {
        GetCamera().SetPosition(0, 0);
        dragging = false;
        return true;
    }
    return false;
}

bool CameraControlService::OnMouseButtonPressed(int button, int x, int y)
{
    if (button != mouseButton) {
        return false;
    }

    startScreenPos.Set(static_cast<float>(x), static_cast<float>(y));
    startWorldPos = GetCamera().GetPosition();
    dragging = true;

    return true;
}

bool CameraControlService::OnMouseButtonReleased(int button, int x, int y)
{
    if (button != mouseButton || !dragging) {
        return false;
    }

    UpdateCamera(x, y);
    dragging = false;
    return true;
}

void CameraControlService::UpdateCamera(int screenX, int screenY)
{
    auto curScreenPos 
        = Vector2f(static_cast<float>(screenX), static_cast<float>(screenY));

    auto deltaWorld = GetCamera()
        .GetInverseMatrix()
        .TransformVector(startScreenPos - curScreenPos);

    GetCamera().SetPosition(startWorldPos + deltaWorld);
}

