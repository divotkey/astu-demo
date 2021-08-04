# Minimum required CMAKE version.
cmake_minimum_required(VERSION 3.1)

# Set project name (required by CMake)
project(AstuExamples)

# ASTU Library, must be in subdirectory 'astu'
add_subdirectory(${PROJECT_SOURCE_DIR}/astu astu)

# Collection of Sub-projects
add_subdirectory(${PROJECT_SOURCE_DIR}/src/HelloAstu helloastu)
#add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameBoilerplate game_boilerplate)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameBoilerplate10 game_boilerplate_0_10)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameSceneGraph game_scenegraph)

# Small Demo Application related to 2D Game development
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game\ Basics/Scene\ Graph\ Demo\ 1 scene_graph_demo1)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game\ Basics/Scene\ Graph\ Demo\ 2 scene_graph_demo2)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game\ Basics/Scene\ Graph\ Demo\ 3 scene_graph_demo3)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game\ Basics/Camera\ Demo camera_demo)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game\ Basics/Entity\ Demo\ 1 entity_demo1)

# Playable Demo Games
#add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameAsteroids game_asteroids)
