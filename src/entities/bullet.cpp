#include "bullet.hpp"
#include "game.hpp"
#include "util.hpp"

Bullet::Bullet(Vector2 position, double rotation_degrees) : Node(position, 16, 16, rotation_degrees)
{
    this->set_sprite("assets/img/bullet.bmp");
    this->set_sprite_size(width, height);
}


void Bullet::physics_process(float delta)
{
    move();

    // TODO: check collision with all asteroids
}