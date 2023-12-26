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
    Vector2 global_position = get_global_position();
    if (global_position.x < 0 || global_position.x > 1920 || global_position.y < 0 || global_position.y > 1080)
    {
        marked_for_deletion = true;
    }

    // TODO: check collision with all asteroids
}