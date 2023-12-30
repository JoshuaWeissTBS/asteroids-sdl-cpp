#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"
#include "node.hpp"

using namespace std;

class Asteroid : public Node {
public:
    Asteroid(Vector2 position, double width, double height, double rotation_degrees = 0);

    int health = 10;
    void input(SDL_Event *event) override;
    void physics_process(float delta) override;
    void on_collision(Node* node) override;
};

#endif
