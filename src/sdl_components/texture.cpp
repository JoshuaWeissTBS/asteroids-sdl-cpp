#include "texture.hpp"
#include "game.hpp"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::load_from_file (const char *path)
{
    free();

    SDL_Texture* new_texture = NULL;

    // Load image at specified path
    SDL_Surface* loaded_surface = SDL_LoadBMP(path);

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    if (new_texture == NULL) {
        printf("Unable to create texture from %s | SDL Error: %s\n", path, SDL_GetError());
        SDL_FreeSurface(loaded_surface);
        return false;
    } else {
        // Get image dimensions
        width = loaded_surface->w;
        height = loaded_surface->h;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loaded_surface);

    texture = new_texture;
    new_texture = NULL;

    return true;
}

void Texture::free()
{
    // Free texture if it exists
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y)
{
    // Set rendering space and render to screen
    SDL_Rect render_quad = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &render_quad);
}