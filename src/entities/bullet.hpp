#ifndef BULLET_HPP
#define BULLET_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"
#include "node.hpp"

using namespace std;

class Bullet : public Node {
public:
    Bullet(Vector2 position, double rotation_degrees = 0);

    int speed = 20;

    void physics_process(float delta) override;
    void on_collision(Node* node) override;

};

#endif
