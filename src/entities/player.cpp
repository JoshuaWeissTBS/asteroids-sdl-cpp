#include "player.hpp"
#include "util.hpp"
#include "game.hpp"
#include "bullet.hpp"

Player::Player(Vector2 position, int width, int height, double rotation_degrees) : Node(position, width, height, rotation_degrees)
{
    name = "Player";
    set_sprite("assets/img/spaceship.bmp");
    set_sprite_size(width, height);

    // 2 Nodes are added to the player, one for each bullet spawn point
    Node *left_bullet_spawn = new Node(Vector2(-21, -11), 0, 0, 0);
    Node *right_bullet_spawn = new Node(Vector2(21, -11), 0, 0, 0);

    left_bullet_spawn->name = "Left Bullet Spawn";
    right_bullet_spawn->name = "Right Bullet Spawn";

    add_child(left_bullet_spawn);
    add_child(right_bullet_spawn);
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

    if (input_direction.y == -1) {
        velocity.y += input_direction.y * facing_direction.y * acceleration * delta;
        velocity.x += input_direction.y * facing_direction.x * acceleration * delta;
    } else {
        Vector2 normalized = velocity.normalized();
        velocity.y = Util::move_toward(velocity.y, 0, abs(normalized.y) * deceleration * delta);
        velocity.x = Util::move_toward(velocity.x, 0, abs(normalized.x) * deceleration * delta);
    }

    double length = velocity.length();
    if (length > max_speed) {
        velocity = velocity.normalized() * max_speed;
    }

    // Keyboard inputs
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE])
    {
        _shoot();
    }

    move();
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

void Player::_shoot()
{
    // TODO: shoot should be a method on player
    // Shoot 2 bullet from player ship guns
    Vector2 direction = player->get_direction().rotated(-(M_PI / 2));

    // TODO: shouldn't really access bullet spawn points like this
    Vector2 bullet_position = player->children[0]->get_global_position();
    Vector2 bullet_position2 = player->children[1]->get_global_position();

    Bullet *bullet = new Bullet(bullet_position, player->rotation_degrees);
    Bullet *bullet2 = new Bullet(bullet_position2, player->rotation_degrees);

    bullet->velocity.x = direction.x * bullet->speed;
    bullet->velocity.y = direction.y * bullet->speed;

    bullet2->velocity.x = direction.x * bullet2->speed;
    bullet2->velocity.y = direction.y * bullet2->speed;

    parent->add_child(bullet);
    parent->add_child(bullet2);
}
