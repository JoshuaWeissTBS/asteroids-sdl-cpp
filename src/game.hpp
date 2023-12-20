#ifndef GAME_HPP
#define GAME_HPP
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include <iostream>
#include "node.hpp"
#include <vector>

using namespace std;

extern SDL_Renderer *renderer;
extern SDL_Window *screen_window;
class Game {
public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    // Other member functions and variables
    bool running = false;
    const char *title = "Asteroids";
    int max_fps = 60;
    int width = 1920;
    int height = 1080;
    vector<Node*> nodes; // Would prefer not to use STD
    SDL_Surface *screen_surface;
    SDL_GLContext gl_context;
    int init(bool fullscreen);
    /// @brief Handles input
    void input();
    void update(float delta);
    void draw();
    void cleanup();
    
private:
    void _on_mouse_move(int x, int y);

};

#endif // GAME_HPP
