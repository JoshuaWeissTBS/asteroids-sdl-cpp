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

struct Edge {
    Node* node;
    float x;
    bool is_left;
};

void Util::get_collisions(vector<Node*> nodes)
{
    // Sweep and prune algorithm
    vector<Edge> edges;

    for (int i = 0; i < nodes.size(); i++)
    {
        Node* node = nodes[i];
        node->collisions_last_frame = node->collisions;
        node->collisions = {};

        Edge left_edge;
        left_edge.node = node;
        left_edge.x = node->get_left();
        left_edge.is_left = true;

        Edge right_edge;
        right_edge.node = node;
        right_edge.x = node->get_right();
        right_edge.is_left = false;

        edges.push_back(left_edge);
        edges.push_back(right_edge);
    }


    vector<Edge> touching;
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.x < b.x;
    });

    for (int i = 0; i < edges.size(); i++)
    {
        Edge edge = edges[i];

        if (edge.is_left)
        {
            for (int j = 0; j < touching.size(); j++) {
                Edge edge2 = touching[j];
                if (Util::check_collision(edge.node->collider, edge2.node->collider)) {
                    // If the two nodes collided last frame, don't call on_node_collision again

                    bool collided_last_frame = false;
                    for (int l = 0; l < (int)edge.node->collisions_last_frame.size(); l++)
                    {
                        if (edge.node->collisions_last_frame[l] == edge2.node)
                        {
                            collided_last_frame = true;
                            break;
                        }
                    }

                    if (collided_last_frame == false)
                    {
                        edge.node->on_collision(edge2.node);
                        edge2.node->on_collision(edge.node);
                    }

                    edge.node->collisions.push_back(edge2.node);
                    edge2.node->collisions.push_back(edge.node);
                }
            }

            touching.push_back(edge);
        }
        else
        {
            for (int j = 0; j < touching.size(); j++)
            {
                if (edge.node == touching[j].node)
                {
                    touching.erase(touching.begin() + j);
                    break;
                }
            }
        }
    }
}