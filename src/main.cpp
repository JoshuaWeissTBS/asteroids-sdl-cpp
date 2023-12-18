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

    // asteroid texture
    Texture asteroid_texture = Texture();
    err = asteroid_texture.load_from_file("assets/img/asteroid.bmp", game.renderer);
    if (err == 0) {
        cout << "Asteroid texture loaded" << endl;
    }

    // Game loop
    while (game.running)
    {
        SDL_RenderClear(game.renderer);
        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        game.input();

        // random x y
        game.update(1);

        // Draw/render the game state
        game.draw();
    }

    game.cleanup();

    return 0;
}
