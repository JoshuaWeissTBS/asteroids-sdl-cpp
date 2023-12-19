#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"
#include "node.hpp"

using namespace std;

class Asteroid : public Node {
public:
    void on_ready() override;
    void input(SDL_Event *event) override;
};

#endif
