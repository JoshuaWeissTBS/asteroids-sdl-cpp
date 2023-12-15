#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

bool game_running = true;

void _input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            game_running = false;
        if (event.type == SDL_MOUSEMOTION)
            cout << "Mouse moved" << " " << event.motion.x << "," << event.motion.y << endl;
        if (event.type == SDL_KEYDOWN)
            cout << "Key pressed" << event.key.keysym.scancode << endl;
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

    SDL_Window *window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        return 1;
    }

    while (game_running)
    {
        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        _input();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
