#ifndef GAME_HPP
#define GAME_HPP
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include <iostream>

using namespace std;

class Game {
public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    // Other member functions and variables
    bool running = false;
    const char *title = "Asteroids";
    int width = 1920;
    int height = 1080;
    SDL_Window *screen_window;
    SDL_Surface *screen_surface;
    SDL_GLContext gl_context;
    int init(bool fullscreen);
    /// @brief Handles input
    void input();
    void draw();
    void cleanup();
    void _on_mouse_move(int x, int y);

};

#endif // GAME_HPP
