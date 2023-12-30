# asteroids-sdl-cpp

This project is a robust and flexible game engine built from scratch using C++ and SDL2. It is currently made to run Asteroids, but it is designed to handle a wide variety of game types and scenarios, with a focus on performance and to be easily extendable.

## Core Features

### Node-Based Architecture

The engine uses a node-based architecture, where each game object is a node that can have a parent and multiple children. This allows for a highly modular and scalable structure, where complex scenes can be built up from simpler components.

The engine provides a base `Node` class that can be used as-is or extended to create new types of nodes. This makes it easy to add new types of game objects or customize the behavior of existing ones.

### Physics and Collision Detection

The engine includes support for velocity and collision detection. Each node keeps track of the nodes it is currently colliding with, as well as the nodes it collided with in the last frame. This allows for complex interactions between game objects. The engine uses a broad-phase collision detection algorithm, sweep and prune, for efficient large scale collision detection.

The engine includes a `Vector2` class, which is used to represent 2D vectors. This class is used extensively throughout the engine to represent positions, velocities, and directions. It includes many methods for common vector operations.

### Input Handling

The engine has a flexible input handling system, where each node can handle its own input events. This allows for a high degree of interactivity and control over game objects.

### Rendering

The engine uses SDL2 for rendering, with support for textures and rotation. Each node has a position, width, height, and rotation, which are used to determine how it is rendered on the screen.

### Memory Management

The engine includes a system for marking nodes for deletion, allowing for efficient memory management. Nodes that are marked for deletion are automatically removed at the end of the frame.

### OpenGL Rendering
The engine supports OpenGL rendering facilitated by the GLAD loader.

## Future Enhancements

The engine is designed to be easily extendable, with several potential areas for future enhancement:

### Animation Support

Implement a system for handling sprite-based animations. This could involve creating an `Animation` class that can cycle through a series of textures based on a set timeframe.

### UI Support
Implement a UI system to handle user interface elements such as buttons, sliders, text boxes, and menus. This system should be separate from the game's main rendering and update loop to ensure that UI elements are always drawn on top and are not affected by the game's camera movements or transformations. The UI system could include a variety of pre-built UI components, a UI layout system, and support for UI animations and transitions.

### Dedicated engine GUI
Create a GUI for users of this engine to allow for better ease of use when creating games.

## Start game

Cmake build (from src folder):

`cmake --build ./build/`
