#include "node.hpp"
#include "vector2.hpp"
#include "texture.hpp"
#include <iostream>

Node::Node(Vector2 position, int width, int height, int rotation_degrees = 0)
{
    // TODO: Do I need to check if position is out of bounds?
    this->position = position;
    this->width = width;
    this->height = height;
    this->rotation_degrees = rotation_degrees;
    this->velocity = Vector2(0, 0);
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

void Node::move()
{
    position.x += velocity.x;
    position.y += velocity.y;
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

    texture->render(position.x, position.y);
}

void Node::physics_process(float delta)
{
}