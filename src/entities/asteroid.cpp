#include "asteroid.hpp"
#include "game.hpp"
#include "util.hpp"

Asteroid::Asteroid(Vector2 position, int width, int height, double rotation_degrees) : Node(position, width, height, rotation_degrees)
{
    name = "Asteroid";

    this->set_sprite("assets/img/asteroid.bmp");
    this->set_sprite_size(width, height);
}

void Asteroid::input(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        cout << "Asteroid clicked" << endl;
        break;
    }
}

void Asteroid::physics_process(float delta)
{
    this->rotation_degrees += 1;
    move();

    // if (Util::check_collision(this->collider, player->collider))
    // {
    //     cout << "Asteroid collided with player" << endl;
    //     marked_for_deletion = true;
    // }
}
