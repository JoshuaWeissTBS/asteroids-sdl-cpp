#ifndef NODE_HPP
#define NODE_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"

using namespace std;

class Node {
public:
    // Constructor
    Node(Vector2 position, int width, int height, int rotation_degrees);

    // Destructor
    ~Node();

    Vector2 position;
    Vector2 velocity;
    float rotation_degrees; // not implemented yet
    int width;
    int height;
    virtual void input(SDL_Event *event);
    virtual void on_ready();
    void set_sprite(const char * path);
    void move(float delta); // Should be called once per frame
    void render(); // Call once per frame after move() and other properties have been updated

private:
    Texture *texture;
};

#endif
