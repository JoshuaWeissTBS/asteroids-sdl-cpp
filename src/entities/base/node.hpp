#ifndef NODE_HPP
#define NODE_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"
#include <vector>
#include <string>

using namespace std;

/// This class' implementation should be left alone as it is a base node class
/// Either use this node as is or create a new node class that inherits from this one

class Node {
public:
    // Constructor
    Node(Vector2 position, double width, double height, double rotation_degrees);

    // Destructor
    ~Node();

    string name = "Node";
    /// @brief The position of the node relative to its parent
    Vector2 position;
    Vector2 velocity;
    double rotation_degrees;
    double width;
    double height;
    Node* parent = NULL;
    vector<Node*> children = {};
    // @brief A vector of nodes that this node is colliding with in this frame, updated after physics_process()
    vector<Node*> collisions = {};
    // @brief A vector of nodes that this node was colliding with in the last frame
    vector<Node*> collisions_last_frame = {};

    // If true, the node will be deleted at the end of the frame
    bool marked_for_deletion = false;

    /// @brief Handles input
    virtual void input(SDL_Event *event);

    /// @brief Input that is called by parent nodes once per frame, which invokes input() on all children. Called in a bottom-top approach. Should not be overriden.
    /// @param event
    void _input(SDL_Event *event);

    /// @brief Called once per frame, meant to be overridden by child classes
    /// @param delta
    virtual void physics_process(float delta);

    /// @brief Physics process that is called by parent nodes once per frame, which invokes physics_process() on all children. Called in a top-bottom approach. Should not be overriden. 
    /// @param delta
    void _physics_process(float delta);

    /// @brief Gets the direction the node is facing as a Vector2
    /// @return Vector2
    Vector2 get_direction();

    /// @brief Gets the global position of the node
    /// @return Vector2
    Vector2 get_global_position();

    /// @brief Sets the sprite of the node (texture internally)
    /// @param path The path to the image file
    void set_sprite(const char * path);

    /// @brief Sets the size of the sprite
    /// @param width 
    /// @param height 
    void set_sprite_size(float width, float height);

    /// @brief Add child node to this node
    /// @param node
    void add_child(Node *node);

    /// @brief Updates the position of the node based on its velocity, recursively calls move() on all children
    void move();

    /// @brief Renders the node to the screen, called once per frame after move() and other properties have been updated
    void render();

    /// @brief Gets all children nodes recursively and returns them in a vector
    /// @return the vector of nodes
    vector<Node*> get_all_nodes();

    /// @brief Signal func that is called whenever a node collides with this node
    /// @param node The node that collided with this node
    virtual void on_collision(Node *node);

    SDL_FRect collider;

    /// @brief Gets the left edge of the collider
    /// @return the left edge of the collider
    float get_left();

    /// @brief Gets the right edge of the collider
    /// @return the right edge of the collider
    float get_right();

    /// @brief Gets the top edge of the collider
    /// @return the top edge of the collider
    float get_top();

    /// @brief Gets the bottom edge of the collider
    /// @return the bottom edge of the collider
    float get_bottom();

private:
    Texture *texture = NULL;
    /// @brief The position of the node relative to the screen
    Vector2 global_position = { 0, 0 };
};

#endif
