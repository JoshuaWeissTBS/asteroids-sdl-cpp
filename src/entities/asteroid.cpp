#include "asteroid.hpp"
#include "game.hpp"

void Asteroid::on_ready()
{
    this->velocity = Vector2(0, 0);
    this->set_sprite("assets/asteroid.png");
}

void Asteroid::input(SDL_Event *event)
{

}