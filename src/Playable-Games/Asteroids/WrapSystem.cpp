/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "WrapSystem.h"
#include "CWrap.h"

// AST Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily WrapSystem::FAMILY = EntityFamily::Create<CWrap, CPose>();

WrapSystem::WrapSystem(int updatePriority)
	  : BaseService("Wrap System")
	  , IteratingEntitySystem(FAMILY, updatePriority)    
{
	// Intentionally left empty.
}

void WrapSystem::OnStartup()
{
	// Intentionally left empty.
}

void WrapSystem::OnShutdown()
{
	// Intentionally left empty.
}

void WrapSystem::ProcessEntity(Entity & entity)
{
	auto& wrap = entity.GetComponent<CWrap>();
	auto& pose = entity.GetComponent<CPose>();
	const auto& p = pose.transform.GetTranslation();

	if (p.x > wrap.rightBoundary) {
		pose.transform.SetTranslationX(wrap.leftBoundary);
	} else if (p.x < wrap.leftBoundary) {
		pose.transform.SetTranslationX(wrap.rightBoundary);
	}

	if (p.y > wrap.topBoundary) {
		pose.transform.SetTranslationY(wrap.bottomBoundary);
	} else if (p.y < wrap.bottomBoundary) {
		pose.transform.SetTranslationY(wrap.topBoundary);
	}
}