#include "asteroid.hpp"
#include "game.hpp"

Asteroid::Asteroid(Vector2 position, int width, int height, int rotation_degrees) : Node(position, width, height, rotation_degrees)
{
    this->set_sprite("assets/img/asteroid.bmp");
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