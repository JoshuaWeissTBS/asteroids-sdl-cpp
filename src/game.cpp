#include "game.hpp"
#include "util.hpp"
#include "sdl_components/texture.hpp"
#include "entities/node.cpp"
#include "vector2.cpp"

Game::Game()
{
}

Game::~Game()
{
}

int Game::init(bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Specify OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Color bit depth
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (fullscreen) {
        window_flags = (SDL_WindowFlags)(window_flags | SDL_WINDOW_FULLSCREEN);
    }

    screen_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
    if (screen_window == NULL) {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(screen_window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "SDL_CreateRenderer failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    screen_surface = SDL_GetWindowSurface(screen_window);
    if (screen_surface == NULL) {
        cout << "SDL_GetWindowSurface failed: " << SDL_GetError() << endl;
        return 1;
    }

    gl_context = SDL_GL_CreateContext(screen_window);
    if (gl_context == NULL) {
        cout << "SDL_GL_CreateContext failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Setup function pointers
    if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
        cout << "Failed to initialize OpenGL context" << endl;
        return 1;
    }

    glViewport(0, 0, 1920, 1080);

    return 0;
}

void Game::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEMOTION:
                _on_mouse_move(event.motion.x, event.motion.y);
                break;
        }

        // Keyboard inputs
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            running = false;
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            cout << "Left arrow pressed" << endl;
            int x = rand() % 1920;
            int y = rand() % 1080;
            Node asteroid = Node(Vector2(x, y), 100, 100);
            asteroid.velocity = Vector2(100, 100);
            asteroid.set_sprite("assets/img/asteroid.bmp", renderer);
            nodes.push_back(asteroid);
        }
    }
}

void Game::update(float delta)
{
    // Loop through all nodes and update their properties
    for (int i = 0; i < nodes.size(); i++) {
        cout << "Node " << i << " position: " << nodes[i].position.x << ", " << nodes[i].position.y << endl;
        nodes[i].move(delta);
    }
}

void Game::draw()
{
    // Loop through all nodes and render them
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].render(renderer);
    }

    //SDL_UpdateWindowSurface(screen_window);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderPresent(renderer);
    // SDL_GL_SwapWindow(screen_window);
}

void Game::cleanup()
{
    SDL_GL_DeleteContext(gl_context);
    gl_context = NULL;

    SDL_DestroyWindow(screen_window);
    screen_surface = NULL;
    screen_window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
}

void Game::_on_mouse_move(int x, int y)
{
    SDL_LockSurface(screen_surface);

    // Set pixel color at mouse position
    Uint32 *pixels = (Uint32 *)screen_surface->pixels;

    int radius = 50;
    Util util;

    for (int i = 0; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {
            int top_pixel = (y - i) * screen_surface->w + x + j;
            if (!util.pixel_out_of_bounds(screen_surface->w, screen_surface->h, x + j, y - i)) {
                pixels[top_pixel] = SDL_MapRGB(screen_surface->format, x % 255, y % 255, x + y % 255);
            }

            int bot_pixel = (y + i) * screen_surface->w + x + j;
            if (!util.pixel_out_of_bounds(screen_surface->w, screen_surface->h, x + j, y + i)) {
                pixels[bot_pixel] = SDL_MapRGB(screen_surface->format, x % 255, y % 255, x + y % 255);
            }
        }
    };
    
    SDL_UnlockSurface(screen_surface);
}

