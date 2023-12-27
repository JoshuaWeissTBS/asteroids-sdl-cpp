#include "util.hpp"
#include <iostream>
#include <bits/stdc++.h>

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

bool Util::check_y_axis_collision(SDL_Rect a, SDL_Rect b)
{
    // The sides of the rectangles
    int top_a, top_b;
    int bottom_a, bottom_b;
    
    // Calculate the sides of rect A
    top_a = a.y;
    bottom_a = a.y + a.h;

    // Calculate the sides of rect B
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

    // If none of the sides from A are outside B
    return true;
}

float Util::degrees_to_radians(float degrees)
{
    return degrees * (M_PI / 180);
}

float Util::radians_to_degrees(float radians)
{
    return radians * (180 / M_PI);
}

double Util::clamp (double value, double min, double max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

vector<vector<Node*>> Util::get_collisions(vector<Node*> nodes)
{
    vector<vector<Node*>> possible_collisions;
    
    // Sweep and prune algorithm
    // Sort nodes by x position
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->get_global_position().x < b->get_global_position().x;
    });

    // Iterate through nodes and check for possible collisions
    // If the distance between two nodes is less than the sum of their widths, they are possible collisions

    vector<Node*> possible_collisions_for_node;
    for (int i = 0; i < nodes.size(); i++)
    {

        if (i == 0)
        {
            possible_collisions_for_node.push_back(nodes[i]);
        }
        else
        {
            if (nodes[i]->get_global_position().x - nodes[i - 1]->get_global_position().x < nodes[i]->width + nodes[i - 1]->width) {
                possible_collisions_for_node.push_back(nodes[i]);
            } else {
                possible_collisions.push_back(possible_collisions_for_node);
                possible_collisions_for_node.clear();
                possible_collisions_for_node.push_back(nodes[i]);
            }
        }
    }
    possible_collisions.push_back(possible_collisions_for_node);

    // Iterate through possible collisions and check for actual collisions
    vector<vector<Node*>> collisions;

    for (int i = 0; i < possible_collisions.size(); i++)
    {
        for (int j = 0; j < possible_collisions[i].size(); j++)
        {
            for (int k = j + 1; k < possible_collisions[i].size(); k++)
            {
                if (Util::check_y_axis_collision(possible_collisions[i][j]->collider, possible_collisions[i][k]->collider))
                {
                    vector<Node*> collision = {possible_collisions[i][j], possible_collisions[i][k]};
                    collisions.push_back(collision);
                }
            }
        }
    }

    return collisions;
}
