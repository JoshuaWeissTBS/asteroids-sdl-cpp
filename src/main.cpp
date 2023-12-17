#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>

using namespace std;

bool game_running = true;
SDL_Surface *screen_surface;
SDL_GLContext gl_context;

bool pixel_out_of_bounds(SDL_Surface *surface, int x, int y) {
    int pixel_index = y * screen_surface->w + x;
    int pixels_length = screen_surface->w * screen_surface->h;
    int pixel_row = pixel_index / screen_surface->w;

    if (pixel_index < 0 || pixel_index > pixels_length) {
        return true;
    }

    if (pixel_row != y) {
        return true;
    }

    return false;
}

void on_mouse_move(int x, int y)
{
    SDL_LockSurface(screen_surface);

    // Set pixel color at mouse position
    Uint32 *pixels = (Uint32 *)screen_surface->pixels;

    int radius = 30;

    for (int i = 0; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {
            int top_pixel = (y - i) * screen_surface->w + x + j;
            if (!pixel_out_of_bounds(screen_surface, x + j, y - i)) {
                pixels[top_pixel] = SDL_MapRGB(screen_surface->format, x % 255, y % 255, x + y % 255);
            }

            int bot_pixel = (y + i) * screen_surface->w + x + j;
            if (!pixel_out_of_bounds(screen_surface, x + j, y + i)) {
                pixels[bot_pixel] = SDL_MapRGB(screen_surface->format, x % 255, y % 255, x + y % 255);
            }
        }
    };

    SDL_UnlockSurface(screen_surface);

    // Update the window surface
    SDL_UpdateWindowSurface(SDL_GetWindowFromID(1));
}

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
                on_mouse_move(event.motion.x, event.motion.y);
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

void _draw(SDL_Window *sdl_window, SDL_Surface *surface) {
    // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    SDL_GL_SwapWindow(sdl_window);
}

void _init_gl() {
    // Specify OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Color bit depth
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

int main()
{
    int started = SDL_Init(SDL_INIT_EVERYTHING);
    if (started != 0)
    {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    _init_gl();

    SDL_Window *sdl_window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (sdl_window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        return 1;
    }

    screen_surface = SDL_GetWindowSurface(sdl_window);

    gl_context = SDL_GL_CreateContext(sdl_window);

    // Setup function pointers
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    if (gl_context == NULL)
    {
        cout << "SDL_GL_CreateContext failed: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_Surface *asteroid_surface;
    asteroid_surface = SDL_LoadBMP("./assets/img/asteroid.bmp");
    SDL_BlitSurface(asteroid_surface, NULL, screen_surface, NULL);
    SDL_FreeSurface(asteroid_surface);

    SDL_UpdateWindowSurface(sdl_window);


    while (game_running)
    {
        
        glViewport(0, 0, 500, 500);

        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        _input();

        // Draw/render the game state
        _draw(sdl_window, screen_surface);
    }

    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    return 0;
}
