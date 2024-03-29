#ifndef GAME_HPP
#define GAME_HPP
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include <iostream>
#include "node.hpp"
#include <vector>
#include "player.hpp"

using namespace std;

extern SDL_Renderer *renderer;
extern SDL_Window *screen_window;
extern Player *player;
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
    Node* root_node = new Node(Vector2(0, 0), 0, 0, 0);
    SDL_Surface *screen_surface;
    SDL_GLContext gl_context;
    int init(bool fullscreen);
    /// @brief Handles input
    void input();
    void update(float delta);
    void draw();
    void cleanup();
};

#endif // GAME_HPP
