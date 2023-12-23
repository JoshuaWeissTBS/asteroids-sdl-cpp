#include "util.hpp"
#include <iostream>

using namespace std;

Util::Util()
{
}

Util::~Util()
{
}

bool Util::pixel_out_of_bounds(int surface_width, int surface_height, int x, int y)
{
    int pixel_index = y * surface_width + x;
    int pixels_length = surface_width * surface_height;
    int pixel_row = pixel_index / surface_width;

    if (pixel_index < 0 || pixel_index > pixels_length) {
        return true;
    }

    if (pixel_row != y) {
        return true;
    }

    return false;
}

float Util::move_toward(float current, float target, float max_delta)
{
    if (current < target)
    {
        current += max_delta;
        if (current > target)
        {
            current = target;
        }
    }
    else if (current > target)
    {
        current -= max_delta;
        if (current < target)
        {
            current = target;
        }
    }
    return current;
}

bool Util::check_collision(SDL_Rect a, SDL_Rect b)
{
    // The sides of the rectangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;
    
    // Calculate the sides of rect A
    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    // Calculate the sides of rect B
    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottom_a <= top_b)
    {
        return false;
    }

    if (top_a >= bottom_b)
    {
        return false;
    }

    if (right_a <= left_b)
    {
        return false;
    }

    if (left_a >= right_b)
    {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}