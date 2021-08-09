/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Some Notes about original Atari's Asteroids
// Big Asteroid width = 6.8 % of screen width
// small asteroid width = 2.1 % of screen width
// ship length = 3.24 % of screen width

// AST Utilities includes
#include <AstuGraphics.h>
#include <AstuInput.h>

/////////////////////////////////////////////////
/////// General constants
/////////////////////////////////////////////////
#define WORLD_WIDTH                 94.0f
#define WORLD_HEIGHT                (WORLD_WIDTH * 0.5625f)
#define BOUNDARY_THICKNESS          0.5f
#define BACKGROUND_COLOR            RalColors::TrafficBlack
#define BOUNDARY_COLOR              RalColors::TrafficGreen
#define COLLIDER_COLOR              RalColors::TurquoiseBlue
#define TEXT_COLOR                  RalColors::TrafficGreyA
#define SCORE_POS_X                 (WORLD_WIDTH * -0.35f)
#define SCORE_POS_Y                 (WORLD_HEIGHT * -0.48f)
#define LIFE_POS_X                  SCORE_POS_X
#define LIFE_POS_Y                  (SCORE_POS_Y + 2.50f)
#define MESSAGE_POS_X               0
#define MESSAGE_POS_Y               (WORLD_HEIGHT * 0.47f)
#define MESSAGE_TEXT                "© 1979 ATARI INC"
#define EXTRA_LIFE                  10000

/////////////////////////////////////////////////
/////// Constants for game entities
/////////////////////////////////////////////////

#define SHIP_RADIUS                 0.5f
#define SHIP_COLOR                  astu::RalColors::TrafficWhite
#define SHIP_MAX_TORQUE             7.5f
#define SHIP_MAX_THRUST             15.0f
#define SHIP_ANGULAR_DAMPING        15.0f
#define SHIP_LINEAR_DAMPING         0.35f
#define SHIP_SPAWN_DELAY            1.0f
#define SHIP_DEBRIS_COLOR           SHIP_COLOR
#define SHIP_DEBRIS_NUM_FRAGMENGS   100
#define SHIP_DEBRIS_TTL             2.0f
#define SHIP_THRUST_COLOR           SHIP_COLOR
#define SHIP_THRUST_TTL             0.5f
#define SHIP_THRUST_OFFSET          astu::Vector2f(0.0f, 0.6f)
#define SHIP_THRUST_NUM_FRAGMENTS   350
#define SHIP_THRUST_SPAWN_RADIUS    0.1f

#define GUN_FIRERATE                0.05f
#define GUN_MUZZLE_VELOCITY         50.0f
#define GUN_MOUNT_POINT             astu::Vector2f(0.0f, -0.65f)
#define GUN_DIRECTION               astu::Vector2f(0.0f, -1.0f)

#define ASTEROID_COLOR              astu::RalColors::TrafficOrange
#define ASTEROID_MIN_VELOCITY       3.0f
#define ASTEROID_MAX_VELOCITY       15.0f
#define ASTEROID_NUM_CHILDREN       2
#define BIG_ASTEROID_SCORE          20
#define MEDIUM_ASTEROID_SCORE       50
#define SMALL_ASTEROID_SCORE        100

#define BULLET_COLOR                SHIP_COLOR
#define BULLET_RADIUS               0.1f
#define BULLET_LIFETIME             2.0f
#define BULLETS_DO_WARP             false

#define DEBRIS_COLOR                ASTEROID_COLOR
#define DEBRIS_NUM_FRAGMENGS        10
#define DEBRIS_TTL                  1.0f