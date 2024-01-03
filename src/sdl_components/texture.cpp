#include "texture.hpp"
#include "game.hpp"
#include <glad/glad.h>

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
    if (loaded_surface == NULL) {
        // TODO: throw error instead of printing to stdout
        printf("Unable to load image, likely the path is incorrect %s | SDL Error: %s\n", path, SDL_GetError());
        printf("Current working directory: %s\n", SDL_GetBasePath());
        return false;
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    if (new_texture == NULL) {
        // TODO: throw error instead of printing to stdout
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

int Texture::get_width()
{
    return width;
}

int Texture::get_height()
{
    return height;
}

void Texture::set_size(int width, int height)
{
    // Check if width and height are valid
    if (width <= 0 || height <= 0) {
        // TODO: throw error
        return;
    }
    
    this->width = width;
    this->height = height;
}

void Texture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    if (texture == NULL) {
        // TODO: Throw an error instead of printing to stdout
        // printf("Cannot render texture, texture is NULL\n");
        return;
    }

    // TODO: FEATURE: Param to offset render position/anchor point/ center of rotation
    // Set rendering space and render to screen
    SDL_Rect render_quad = {x - width / 2, y - height / 2, width, height};

    // Set clip rendering dimensions
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &render_quad, angle, center, flip);
}