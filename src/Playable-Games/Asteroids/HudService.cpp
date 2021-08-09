/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "HudService.h"
#include "Constants.h"

// AST Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

#define FPS_WINDOW  1.0

HudService::HudService(int updatePriority)
    : BaseService("Hud Service")
    , Updatable(updatePriority)
{
	  // Intentionally left empty.
}

void HudService::OnStartup()
{
    textRenderer = ASTU_GET_SERVICE(TextRenderService);
    numLifes = 0;
    score = 0;
    dtSum = 0.0;
    dtCnt = 0;
}

void HudService::OnShutdown()
{
    textRenderer = nullptr;
}

bool HudService::OnSignal(const GameEvent& signal)
{
    switch (signal.type) {
    case GameEvent::Type::LifeUpdate:
        numLifes = signal.intValue;
        break;

    case GameEvent::Type::ScoreUpdate:
        score = signal.intValue;
        break;
        
    default:
        break;
    }

    return false;
}

void HudService::OnUpdate()
{  
    // Update FPS
    dtSum += GetElapsedTime();
    ++dtCnt;
    if (dtSum > FPS_WINDOW) {
        fps =  dtCnt / dtSum;
        dtSum = 0;
        dtCnt = 0;
    }

    // Render score.
    textRenderer->SetViewTransform(GetCamera().GetMatrix());
    textRenderer->SetDrawColor(TEXT_COLOR);

    textRenderer->SetAlingment(TextRenderService::Alignment::Right);
    textRenderer->DrawString(SCORE_POS_X, SCORE_POS_Y, to_string(score));

    // Render number of remaining lifes
    SetViewTransform(GetCamera().GetMatrix());
    SetDrawColor(TEXT_COLOR);
    PushTransform();
    SetTranslation(LIFE_POS_X + kShip.radius / 2, LIFE_POS_Y);
    for (int i = 1; i < numLifes; ++i) {
        DrawPolygon(kShip.vertices);
        Translate(-kShip.radius * 2.0f, 0.0f);
    }
    PopTransform();

    // Render Text Message
    textRenderer->SetAlingment(TextRenderService::Alignment::Center);
    textRenderer->DrawString(MESSAGE_POS_X, MESSAGE_POS_Y, MESSAGE_TEXT);
    // textRenderer->DrawString(MESSAGE_POS_X, MESSAGE_POS_Y, "FPS " + to_string((int)(fps)));
}
