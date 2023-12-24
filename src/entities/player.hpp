#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SDL2/SDL.h"
#include "vector2.hpp"
#include "texture.hpp"
#include "node.hpp"

using namespace std;

class Player : public Node {
public:
    Player(Vector2 position, int width, int height, double rotation_degrees = 0);

    int max_speed = 10;
    int acceleration = 20;
    int deceleration = 10;
    void input(SDL_Event *event) override;
    void physics_process(float delta) override;

private:
    /// @brief Checks movement input and returns a vector2 representing the direction to move
    /// @return Vector2 representing the direction to move
    Vector2 _get_move_input_direction();
};

#endif
