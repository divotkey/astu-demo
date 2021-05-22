# Minimum required CMAKE version.
cmake_minimum_required(VERSION 3.1)

# Set project name (required by CMake)
project(AstuExamples)


# ASTU Library, must be in subdirectory 'astu'
add_subdirectory(${PROJECT_SOURCE_DIR}/astu astu)

# Collection of Sub-projects
add_subdirectory(${PROJECT_SOURCE_DIR}/src/HelloAstu helloastu)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameBoilerplate game_boilerplate)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameSceneGraph game_scenegraph)
