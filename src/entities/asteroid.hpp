#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"
#include "node.hpp"

using namespace std;

class Asteroid : public Node {
public:
    Asteroid(Vector2 position, int width, int height, int rotation_degrees = 0);

    void input(SDL_Event *event) override;
};

#endif
