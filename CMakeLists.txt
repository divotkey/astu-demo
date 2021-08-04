# Minimum required CMAKE version.
cmake_minimum_required(VERSION 3.1)

# Set project name (required by CMake)
project(AstuExamples)

# ASTU Library, must be in subdirectory 'astu'
add_subdirectory(${PROJECT_SOURCE_DIR}/astu astu)

# Small Examples using AST-Utilites API-Level 0
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ASTU-Basics/Hello\ Astu helloastu)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ASTU-Basics/Number\ Guessing\ Game number_guessing)

# Small Demo Application related to 2D Game development
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game-Basics/Scene\ Graph\ Demo\ 1 scene_graph_demo1)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game-Basics/Scene\ Graph\ Demo\ 2 scene_graph_demo2)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game-Basics/Scene\ Graph\ Demo\ 3 scene_graph_demo3)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game-Basics/Camera\ Demo camera_demo)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Game-Basics/Entity\ Demo\ 1 entity_demo1)

# Playable Demo Games
#add_subdirectory(${PROJECT_SOURCE_DIR}/src/Playable-Games Asteroids\ Clone)
