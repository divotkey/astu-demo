/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// AST Utilities includes
#include <AstuECS.h>

class CWrap : public astu::EntityComponent {
public: 
	/** Defines the left boundary of the entity. */
	float leftBoundary;

	/** Defines the right boundary of the entity. */
	float rightBoundary;

	/** Defines the top boundary of the entity. */
	float topBoundary;

	/** Defines the bottom boundary of the entity. */
	float bottomBoundary;

	/**
	 * Constructor.
	 * 
	 * @param width		the with of the usable game world.
	 * @param height	the height of the usable game world.
	 */
	CWrap(float width, float height) 
		: leftBoundary(-width / 2.0f)
		, rightBoundary(width / 2.0f)
		, topBoundary(height / 2.0f)
		, bottomBoundary(-height / 2.0f)
	{
		// Intentionally left empty.
	}

	// Inherited via EntityComponent
	virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<CWrap>(*this);
	}    
};