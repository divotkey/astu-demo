# Scene Graph & Camera Demo

This sample project shows the use of the Scene Graph (2D), as well as the use of cameras and the predefined transformations from world space to screen space.

After starting the application, the user can resize the output window. The dimensions of the game world are visualized with a frame. Additionally, markers are placed at the corners and the centers of the edges. If you now change the size of the output window, additional areas become visible. The initial camera mode is Screen-Space, which does not perform any transformation or scaling. Only the origin of the game world is moved to the center of the output window. 

## Scene Graph Objects

New objects can be created with the left mouse button. These are leaves of the Scene Graph of type Polyline. The vertex buffers for Polyline leaves are generated separately with the help of the `Shape2Generator` auxiliary class, which produces the corresponding vertices with the help of the `Vertex2Builder`. The vertex buffers are saved and used for the respective new scene objects.

## Camera Modes

By pressing the `C` key, you can switch between the different camera modes. The current camera mode is displayed in the title bar.

Currently, the following modes are supported:

- Screen Space
- Fixed Width (always the exact width of the game world is displayed)
- Fixed Height (the exact height of the game world is always displayed)
- Fitting (depending on the aspect ratio, the entire height or width of the game world is displayed)
- Filling (the maximum area is used, possibly parts of the game world are not visible)
- Stretched (the game world gets stretched according to the aspect ratio of the output window).

## Moving the Camera

The camera positon and zoom factor can be controlled with the right mouse button and the mouse wheel. This is realized by the `CameraControlService`. The `HOME` key will restore the
initial camera position (0, 0) and zoom factor.