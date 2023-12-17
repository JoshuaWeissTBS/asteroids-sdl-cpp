#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "game.hpp"

using namespace std;

int main()
{
    Game game = Game();
    int err = game.init(false);
    if (err == 0) {
        game.running = true;
    }

    // Game loop
    while (game.running)
    {
        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        game.input();

        // Draw/render the game state
        game.draw();
    }

    game.cleanup();

    return 0;
}
