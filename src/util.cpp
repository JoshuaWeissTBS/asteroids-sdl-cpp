#include "util.hpp"

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