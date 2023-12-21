#include "player.hpp"
#include "game.hpp"
#include "util.hpp"

Player::Player(Vector2 position, int width, int height, int rotation_degrees) : Node(position, width, height, rotation_degrees)
{
    set_sprite("assets/img/spaceship.bmp");
    set_sprite_size(width, height);
}

void Player::input(SDL_Event *event)
{
}

void Player::physics_process(float delta)
{
    Vector2 input_direction = _get_move_input_direction();
    Vector2 facing_direction = get_direction().rotated(M_PI / 2);

    if (input_direction.x != 0)
    {
        rotation_degrees += 200 * input_direction.x * delta;
    }

    if (input_direction.y == 0)
    {
        Vector2 normalized = velocity.normalized();
        velocity.y = Util::move_toward(velocity.y, 0, abs(normalized.y) * deceleration * delta);
        velocity.x = Util::move_toward(velocity.x, 0, abs(normalized.x) * deceleration * delta);
    } else {
        velocity.y += input_direction.y * facing_direction.y * acceleration * delta;
        velocity.x += input_direction.y * facing_direction.x * acceleration * delta;
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

Vector2 Player::_get_move_input_direction()
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
