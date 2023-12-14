#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

SDL_Window *window = NULL;

int main()
{
    int started = SDL_Init(SDL_INIT_EVERYTHING);
    if (started != 0)
    {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);

    bool game_running = true;
    while (game_running)
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

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
