#include "node.hpp"
#include "vector2.hpp"
#include "texture.hpp"
#include <iostream>

using namespace std;

Node::Node(Vector2 position, int width, int height, double rotation_degrees = 0)
{
    // TODO: Do I need to check if position is out of bounds?
    this->position = position;
    this->width = width;
    this->height = height;
    this->rotation_degrees = rotation_degrees;
    this->velocity = Vector2(0, 0);

    collider.x = position.x;
    collider.y = position.y;
    collider.w = width;
    collider.h = height;
}

Node::~Node()
{
}

void Node::input(SDL_Event *event)
{
}

void Node::set_sprite(const char *path)
{
    if (texture == NULL)
    {
        texture = new Texture();
    }

    bool success = texture->load_from_file(path);
    if (!success)
    {
        // TODO: Throw an error instead of printing to stdout
        printf("Failed to load texture image!\n");
    }
}

Vector2 Node::get_direction()
{
    float radians = rotation_degrees * (M_PI / 180);
    return Vector2(cos(radians), sin(radians));
}

void Node::move()
{
    position.x += velocity.x;
    position.y += velocity.y;
    collider.x = position.x;
    collider.y = position.y;
}

void Node::set_sprite_size(int width, int height)
{
    texture->set_size(width, height);
}

void Node::render()
{
    // TODO: Throw an error instead of printing to stdout
    if (texture == NULL)
    {
        printf("Cannot render node, texture is NULL\n");
        return;
    }

    texture->render(position.x, position.y, NULL, rotation_degrees);
}

void Node::physics_process(float delta)
{
}