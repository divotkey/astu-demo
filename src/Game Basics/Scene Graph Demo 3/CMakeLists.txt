cmake_minimum_required(VERSION 3.1)

# set the project name
project(HelloAstu)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# add executable
file(GLOB SOURCES "*.cpp")
add_executable(SceneGraphDemo3 ${SOURCES})
target_link_libraries(SceneGraphDemo3 astu)

# specify required libraries
target_link_libraries(SceneGraphDemo3 astu)