#include "game.hpp"
#include "util.hpp"
#include "texture.hpp"
#include "node.hpp"
#include "asteroid.hpp"
#include "vector2.hpp"
#include "player.hpp"
#include <glad/glad.h>
#include "shader.hpp"


SDL_Renderer *renderer = NULL;
SDL_Window *screen_window = NULL;
Player *player = NULL;
unsigned int vbo = 0;


Vector2 asteroid_spawn_points[10] = {
    {-100, -100},
    {-100, 1180},
    {2020, -100},
    {2020, 1180},
    {-100, 640},
    {2020, 640},
    {1060, -100},
    {1060, 1180},
    {-100, 1060},
    {2020, 1060}
};

Game::Game()
{
}

Game::~Game()
{
}

int Game::init(bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
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
    if (fullscreen)
    {
        window_flags = (SDL_WindowFlags)(window_flags | SDL_WINDOW_FULLSCREEN);
    }

    screen_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
    if (screen_window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        return 1;
    }

    // renderer = SDL_CreateRenderer(screen_window, -1, SDL_RENDERER_ACCELERATED);
    // if (renderer == NULL)
    // {
    //     cout << "SDL_CreateRenderer failed: " << SDL_GetError() << endl;
    //     return 1;
    // }

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    screen_surface = SDL_GetWindowSurface(screen_window);
    if (screen_surface == NULL)
    {
        cout << "SDL_GetWindowSurface failed: " << SDL_GetError() << endl;
        return 1;
    }

    gl_context = SDL_GL_CreateContext(screen_window);
    if (gl_context == NULL)
    {
        cout << "SDL_GL_CreateContext failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Setup function pointers
    if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
    {
        cout << "Failed to initialize OpenGL context" << endl;
        return 1;
    }

    glViewport(0, 0, 1920, 1080);
    
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);

    // Tells OpenGL how to interpret the data in the buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    ShaderProgramSource source = Shader::parse_shader("res/shaders/basic.shader");

    unsigned int shader = Shader::create_shader(source.vertex_source, source.fragment_source);
    glUseProgram(shader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    // Create player
    // TODO: Move this to a level loader
    player = new Player(Vector2(1920/2, 1080/2), 65, 65);
    root_node->add_child(player);

    Asteroid *asteroid = new Asteroid(Vector2(800, 800), 100, 100);
    root_node->add_child(asteroid);

    return 0;
}

void Game::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        root_node->_input(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
        }


        // Keyboard inputs
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            running = false;
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            // Pick random spawn point
            int spawn_point_index = rand() % 4;

            Asteroid *asteroid = new Asteroid(Vector2(asteroid_spawn_points[spawn_point_index].x, asteroid_spawn_points[spawn_point_index].y), 100, 100);

            // Direction to player
            Vector2 direction = asteroid->position.direction_to(player->position);

            asteroid->velocity.x = direction.x * 5;
            asteroid->velocity.y = direction.y * 5;

            root_node->add_child(asteroid);
        }
    }
}

void Game::update(float delta)
{
    // Spawn asteroids randomly
    static float spawnTimer = 0.0f;
    static float spawnInterval = 0.0f;

    spawnTimer += delta;
    if (spawnTimer >= spawnInterval)
    {
        int numAsteroids = rand() % 3 + 1; // Random number between 1 and 3

        for (int i = 0; i < numAsteroids; i++)
        {
            // Pick random spawn point
            int spawn_point_index = rand() % 10;

            float spawnX = asteroid_spawn_points[spawn_point_index].x;
            float spawnY = asteroid_spawn_points[spawn_point_index].y;
            

            Asteroid *asteroid = new Asteroid(Vector2(spawnX, spawnY), 100, 100);

            // Direction towards player
            Vector2 direction = asteroid->position.direction_to(player->position);

            asteroid->velocity.x = direction.x * 5;
            asteroid->velocity.y = direction.y * 5;

            root_node->add_child(asteroid);
        }

        // Reset spawn timer and generate new spawn interval
        spawnTimer = 0.0f;
        spawnInterval = static_cast<float>(rand() % 5 + 1); // Random number between 1 and 5
    }

    root_node->_physics_process(delta);

    // Update collision table
    vector<Node *> nodes = root_node->get_all_nodes();

    collisions = Util::get_collisions(nodes);
}

void Game::draw()
{
    // root_node->render();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // SDL_UpdateWindowSurface(screen_window);
    // SDL_RenderPresent(renderer);
    SDL_GL_SwapWindow(screen_window);
}

void Game::cleanup()
{
    // TODO: Delete all nodes

    // glDeleteProgram(shader);

    SDL_GL_DeleteContext(gl_context);
    gl_context = NULL;

    SDL_DestroyWindow(screen_window);
    screen_surface = NULL;
    screen_window = NULL;

    // SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
}
