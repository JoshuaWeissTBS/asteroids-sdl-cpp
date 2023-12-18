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
    void set_sprite(const char * path, SDL_Renderer *renderer);
    void move(float delta); // Should be called once per frame
    void render(SDL_Renderer *renderer); // Call once per frame after move() and other properties have been updated

private:
    Texture *texture;
};

#endif
