#include "player.hpp"
#include "game.hpp"
#include "util.hpp"

Player::Player(Vector2 position, int width, int height, int rotation_degrees) : Node(position, width, height, rotation_degrees)
{
    set_sprite("assets/img/spaceship.bmp");
    set_sprite_size(100, 100);
}

void Player::input(SDL_Event *event)
{
}

void Player::physics_process(float delta)
{
    Vector2 direction = _get_move_direction();

    if (direction.x == 0)
    {
        velocity.x = Util::move_toward(velocity.x, 0, deceleration * delta);
    } else {
        velocity.x += direction.x * acceleration * delta;
    }

    if (direction.y == 0)
    {
        velocity.y = Util::move_toward(velocity.y, 0, deceleration * delta);
    } else {
        velocity.y += direction.y * acceleration * delta;
    }

    if (velocity.x > max_speed) {
        velocity.x = max_speed;
    }

    if (velocity.x < -max_speed) {
        velocity.x = -max_speed;
    }

    if (velocity.y > max_speed) {
        velocity.y = max_speed;
    }

    if (velocity.y < -max_speed) {
        velocity.y = -max_speed;
    }
}

Vector2 Player::_get_move_direction()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Vector2 direction = Vector2(0, 0);
    if (state[SDL_SCANCODE_W]) {
        direction.y -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        direction.y += 1;
    }
    if (state[SDL_SCANCODE_A]) {
        direction.x -= 1;
    }
    if (state[SDL_SCANCODE_D]) {
        direction.x += 1;
    }
    return direction;
}
