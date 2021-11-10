# AST Utilities Examples and Demos
A comprehensive collection of examples and demos for the AST Utilities library.

This collection of examples and demo applications is currently under development
and therefore still incomplete. Additional examples will be added continuously.

## Installation and Compiling

This repository contains the AST-Utilities repository as a submodule. It is
recommended to check out the repository with the command:

`git clone --recurse-submodules https://github.com/divotkey/astu-demo.git`.

Some examples require to have Simple Direct Layer - Version 2 (SDL2) installed.

### Ubuntu

On Ubuntu, you may see an error in the CMake file when compiling. The problem is in the CMake file of the Box2D physics engine. The error displayed is that the RandR library headers are not found.

```sudo apt-get install xorg-dev libglu1-mesa-dev``` should fix the problem. 

## Sample Projects

Each subdirectory contains a standalone sample project and a corresponding
README file that contains more detailed information.

### AST-Utilities API-Level 0

This list shows sample programs written with AST-Utilities API level 0. The source code for these examples can be found in the directory `src/ASTU-Basics`.

- Hello Astu
- Number Guessing Game

### Video Games and Interactive Applications

This is a list of demo/sample applications that show how to make games and interactive applications using AST-Utilities. The source code for these examples can be found in the directory `src/Game-Basics`.

#### Smaller Example and Tutorials

- Scene Graph Demo 1
- Scene Graph Demo 2
- Scene Graph Demo 3
- Camera Demo
- Entity Demo 1

#### Playable Demo Games

- Asteroids Clone

## Disclaimer

THIS SOURCE IS PROVIDED AS EDUCATIONAL MATERIAL AND NOT INTENDED TO ADDRESS ALL
REAL WORLD PROBLEMS AND ISSUES IN DETAIL.
