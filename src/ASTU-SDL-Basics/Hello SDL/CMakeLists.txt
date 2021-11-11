# Minimum required CMAKE version.
cmake_minimum_required(VERSION 3.1)

# Set project name (required by CMake)
project(HelloSdl)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add executable Target
add_executable(HelloSdl main.cpp)

# Specify required libraries
target_link_libraries(HelloSdl astu)