#ifndef NODE_HPP
#define NODE_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"

using namespace std;

/// This class' implementation should be left alone as it is a base node class
/// Either use this node as is or create a new node class that inherits from this one

class Node {
public:
    // Constructor
    Node(Vector2 position, int width, int height, int rotation_degrees);

    // Destructor
    ~Node();

    Vector2 position;
    Vector2 velocity;
    float rotation_degrees;
    int width;
    int height;

    /// @brief Handles input
    virtual void input(SDL_Event *event);

    /// @brief Called once per frame, meant to be overridden by child classes
    /// @param delta
    virtual void physics_process(float delta);

    /// @brief Gets the direction the node is facing as a Vector2
    /// @return Vector2
    Vector2 get_direction();

    /// @brief Sets the sprite of the node (texture internally)
    /// @param path The path to the image file
    void set_sprite(const char * path);

    /// @brief Sets the size of the sprite
    /// @param width 
    /// @param height 
    void set_sprite_size(int width, int height);

    /// @brief Updates the position of the node based on its velocity, called once per frame by engine
    void move();

    /// @brief Renders the node to the screen, called once per frame after move() and other properties have been updated
    void render();

private:
    Texture *texture = NULL;
};

#endif
