#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>

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

void _draw(SDL_Window *sdl_window) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    SDL_GL_SwapWindow(sdl_window);
}

int main()
{
    int started = SDL_Init(SDL_INIT_EVERYTHING);
    if (started != 0)
    {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_GLContext gl_context;

    // Specify OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Color bit depth
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *sdl_window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);
    if (sdl_window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        return 1;
    }

    gl_context = SDL_GL_CreateContext(sdl_window);

    // Setup function pointers
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    if (gl_context == NULL)
    {
        cout << "SDL_GL_CreateContext failed: " << SDL_GetError() << endl;
        return 1;
    }

    while (game_running)
    {
        glViewport(0, 0, 500, 500);

        // Handle all input events this frame (mouse, keyboard, etc) before updating the game state and rendering next frame
        _input();

        // Draw/render the game state
        _draw(sdl_window);
    }

    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    return 0;
}
