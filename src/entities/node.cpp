#include "node.hpp"
#include "vector2.hpp"
#include "texture.hpp"
#include <iostream>

#include "util.hpp"

using namespace std;

Node::Node(Vector2 position, int width, int height, double rotation_degrees = 0)
{
    // TODO: Do I need to check if position is out of bounds?
    this->position = position;
    this->width = width;
    this->height = height;
    this->rotation_degrees = rotation_degrees;
    this->velocity = Vector2(0, 0);

    collider.x = position.x - (width / 2);
    collider.y = position.y - (height / 2);
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

void Node::set_sprite_size(int width, int height)
{
    texture->set_size(width, height);
}

Vector2 Node::get_direction()
{
    float radians = rotation_degrees * (M_PI / 180);
    return Vector2(cos(radians), sin(radians));
}

void Node::add_child(Node *node)
{
    node->parent = this;
    children.push_back(node);
}

void Node::move()
{
    position.x += velocity.x;
    position.y += velocity.y;

    Vector2 offset = Vector2(0, 0);
    if (parent != NULL)
    {
        // Childrens' positions are relative to their parent's position
        offset = Vector2(parent->position.x, parent->position.y);
        global_position.x = position.x + offset.x;
        global_position.y = position.y + offset.y;
        // TODO: PERFORMANCE: use transform matrix instead of rotating around anchor point

        // If the parent is rotated, the parent acts as an anchor point for the child to rotate around
        Vector2 rotated_around_anchor = global_position.rotated_around_anchor(Util::degrees_to_radians(parent->rotation_degrees), offset);
        global_position.x = rotated_around_anchor.x;
        global_position.y = rotated_around_anchor.y;
    } else {
        global_position.x = position.x;
        global_position.y = position.y;
    }

    collider.x = global_position.x - (width / 2);
    collider.y = global_position.y - (height / 2);

    for (int i = 0; i < children.size(); i++)
    {
        children[i]->move();
    }
}

Vector2 Node::get_global_position()
{
    return global_position;
}

void Node::render()
{
    // TODO: Throw an error instead of printing to stdout
    if (texture == NULL)
    {
        // printf("Cannot render node, texture is NULL\n");
        return;
    }

    texture->render(global_position.x, global_position.y, NULL, rotation_degrees);
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->render();
    }
}

void Node::physics_process(float delta)
{
}