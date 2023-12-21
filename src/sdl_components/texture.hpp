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
    bool load_from_file (const char *path);
    void free();
    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int get_width();
    int get_height();
    void set_size(int width, int height);

private:
    SDL_Texture *texture = NULL;
    int width = 0;
    int height = 0;
};

#endif // Texture_HPP
