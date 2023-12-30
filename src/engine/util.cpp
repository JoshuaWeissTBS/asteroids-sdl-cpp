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

bool Util::pixel_out_of_bounds(double surface_width, double surface_height, double x, double y)
{
    double pixel_index = y * surface_width + x;
    double pixels_length = surface_width * surface_height;
    double pixel_row = pixel_index / surface_width;

    if (pixel_index < 0 || pixel_index > pixels_length) {
        return true;
    }

    if (pixel_row != y) {
        return true;
    }

    return false;
}

double Util::move_toward(double current, double target, double max_delta)
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

bool Util::check_collision(SDL_FRect a, SDL_FRect b)
{
    // The sides of the rectangles
    float left_a, left_b;
    float right_a, right_b;
    float top_a, top_b;
    float bottom_a, bottom_b;
    
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

double Util::degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180);
}

double Util::radians_to_degrees(double radians)
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
    // Sweep and prune algorithm
    // Sort nodes by x position
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->get_left() < b->get_left();
    });

    vector<vector<Node*>> possible_collisions;

    vector<Node*> active_intervals;
    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->collisions_last_frame = nodes[i]->collisions;
        nodes[i]->collisions.clear();

        if (active_intervals.size() == 0) {
            active_intervals.push_back(nodes[i]);
            continue;
        } 

        for (int j = 0; j < active_intervals.size(); j++)
        {
            if (nodes[i]->get_left() < active_intervals[j]->get_right()) {
                possible_collisions.push_back({nodes[i], active_intervals[j]});
            } else {
                active_intervals.erase(active_intervals.begin() + j);
                j--;
            }
        }
        active_intervals.push_back(nodes[i]);
    }

    // Iterate through possible collisions and check for actual collisions
    vector<vector<Node*>> collisions;

    for (int i = 0; i < possible_collisions.size(); i++)
    {
        if (Util::check_collision(possible_collisions[i][0]->collider, possible_collisions[i][1]->collider))
        {
            // If the two nodes collided last frame, don't call on_node_collision again

            bool collided_last_frame = false;
            for (int l = 0; l < possible_collisions[i][0]->collisions_last_frame.size(); l++)
            {
                if (possible_collisions[i][0]->collisions_last_frame[l] == possible_collisions[i][1])
                {
                    collided_last_frame = true;
                    break;
                }
            }

            if (collided_last_frame == false)
            {
                possible_collisions[i][0]->on_collision(possible_collisions[i][1]);
                possible_collisions[i][1]->on_collision(possible_collisions[i][0]);
            }

            possible_collisions[i][0]->collisions.push_back(possible_collisions[i][1]);
            possible_collisions[i][1]->collisions.push_back(possible_collisions[i][0]);
        }
    }

    return collisions;
}
