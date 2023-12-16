#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

bool game_running = true;

void _input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                game_running = false;
                break;
            case SDL_MOUSEMOTION:
                cout << "Mouse moved" << " " << event.motion.x << "," << event.motion.y << endl;
                break;
            case SDL_KEYDOWN:
                cout << "Key pressed" << event.key.keysym.scancode << endl;
                break;
        }

        // Keyboard inputs
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            game_running = false;
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            cout << "Left arrow pressed" << endl;
        }
    }
}

int main()
{
    int started = SDL_Init(SDL_INIT_EVERYTHING);
    if (started != 0)
    {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window *sdl_window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_VULKAN);
    if (sdl_window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        return 1;
    }

    while (game_running)
    {
        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        _input();
    }

    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    return 0;
}
