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

    // If the bullet is off screen, mark it for deletion
    // TODO: window size
    if (position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080)
    {
        marked_for_deletion = true;
    }

    // TODO: check collision with all asteroids
}