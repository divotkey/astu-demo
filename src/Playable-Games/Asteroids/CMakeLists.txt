cmake_minimum_required(VERSION 3.1)

# set the project name
project(AsteroidsClone)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# add executable
file(GLOB SOURCES "*.cpp")
add_executable(AsteroidsClone ${SOURCES})

IF (WIN32)
    # comment out this line to open a console window even on windows
    set_target_properties(AsteroidsClone PROPERTIES LINK_FLAGS "/subsystem:windows /ENTRY:mainCRTStartup")
ENDIF()

# specify required libraries
target_link_libraries(AsteroidsClone astu astu_box2d)
