#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "game.hpp"
#include "texture.hpp"

using namespace std;

int main()
{
    Game game = Game();
    int err = game.init(false);
    if (err == 0) {
        game.running = true;
    }

    Uint32 last_frame_time = SDL_GetTicks();

    // Game loop
    while (game.running)
    {
        // Calculate delta time
        // Time between this frame and the previous frame in seconds (in 60 fps, delta should be 1/60 = 0.0166666666666667)
        // This is to ensure that the game runs at the same speed on all computers
        Uint32 current_time = SDL_GetTicks();
        float delta = (current_time - last_frame_time) / 1000.0f;
        last_frame_time = current_time;

        // Clear the screen
        SDL_RenderClear(renderer);

        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        game.input();

        // Calls move() or update() on all nodes
        game.update(delta);

        // Draw/render the game state onto the screen
        game.draw();

        // Update the screen
        SDL_RenderPresent(renderer);

        // Cap framerate at 60 FPS
        Uint32 elapsed_time = SDL_GetTicks() - last_frame_time;
        // 16 ms = 1/60 = 60 FPS
        int ms_per_frame = 1000 / game.max_fps;
        if (elapsed_time < ms_per_frame) {
            SDL_Delay(ms_per_frame - elapsed_time);
        }
        int fps = static_cast<int>(round(1000.0 / (SDL_GetTicks() - last_frame_time)));
        cout << "FPS: " << fps << endl;

    }

    game.cleanup();

    return 0;
}
