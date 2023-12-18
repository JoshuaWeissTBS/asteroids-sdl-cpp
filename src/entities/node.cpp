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
    this->texture = NULL;
}

Node::~Node()
{
}

void Node::set_sprite(const char * path, SDL_Renderer *renderer)
{
    if (texture == NULL) {
        texture = new Texture();
    }

    bool success = texture->load_from_file(path, renderer);
    if (!success) {
        printf("Failed to load texture image!\n");
    }
}

void Node::move(float delta)
{
    position.x += velocity.x * delta;
    position.y += velocity.y * delta;
}

void Node::render(SDL_Renderer *renderer)
{
    texture->render(position.x, position.y, renderer);
}