/*
 * Asteroids Clone - Version 1.0.0
 *
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <Vector2.h>

class GameEvent {
public:
    enum Type {
        BIG_ASTEROID_SPAWNED, 
        MEDIUM_ASTEROID_SPAWNED, 
        SMALL_ASTEROID_SPAWNED, 
        SHIP_SPAWNED, 
        BULLED_SPAWNED,
        BIG_ASTEROID_DESTROYED, 
        MEDIUM_ASTEROID_DESTROYED, 
        SMALL_ASTEROID_DESTROYED, 
        SHIP_DESTROYED, 
        BULLED_DESTROYED
        };

    /** The type of this event. */
    Type type;

    /** The position the event has occurred in the game world. */
    astu::Vector2f pos;

    GameEvent(Type type, const astu::Vector2f p = {0, 0})
        : type(type), pos(p) {}
};

class PlayerEvent {
public:
    int level;
    int asteroids;
    int score;

    PlayerEvent(int inLevel, int inAsteroids, int inScore)
        : level(inLevel), asteroids(inAsteroids), score(inScore) {}
};