#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "SDL2/SDL.h"

using namespace std;

class Texture {
public:
    // Constructor
    Texture();

    // Destructor
    ~Texture();

    SDL_Texture *media_texture;
    bool load_from_file (const char *path, SDL_Renderer *renderer);
    void free();
    void render(int x, int y, SDL_Renderer *renderer);
    int get_width();
    int get_height();

private:
    SDL_Texture *texture = NULL;
    int width = 0;
    int height = 0;
};

#endif // Texture_HPP
