#include "node.hpp"
#include "vector2.hpp"
#include "texture.hpp"
#include <iostream>

#include "util.hpp"
#include "game.hpp"

using namespace std;

Node::Node(Vector2 position, double width, double height, double rotation_degrees = 0)
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

// Should not be overridden
void Node::_input(SDL_Event *event)
{
    // Handle input for all nodes
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->_input(event);
    }
    input(event);
}

void Node::physics_process(float delta)
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

void Node::set_sprite_size(float width, float height)
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
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->render();
    }

    // TODO: Throw an error instead of printing to stdout
    if (texture == NULL)
    {
        // printf("Cannot render node, texture is NULL\n");
        return;
    }

    // render collider
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    // SDL_RenderDrawRectF(renderer, &collider);
    // SDL_RenderDrawPointF(renderer, global_position.x, global_position.y);

    texture->render(global_position.x, global_position.y, NULL, rotation_degrees);
}

void Node::_physics_process(float delta)
{
    // TODO: handle deletion
    // Handle physics process for all nodes
    physics_process(delta);
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->_physics_process(delta);

        if (children[i]->marked_for_deletion)
        {
            delete children[i];
            // TODO: PERFORMANCE: erase is expensive, find a better way to do this
            children.erase(children.begin() + i);
            continue;
        }
    }
}

vector<Node*> Node::get_all_nodes()
{
    vector<Node*> nodes = {};

    nodes.push_back(this);

    for (int i = 0; i < children.size(); i++)
    {
        vector<Node*> child_nodes = children[i]->get_all_nodes();
        nodes.insert(nodes.end(), child_nodes.begin(), child_nodes.end());
    }

    return nodes;
}

void Node::on_collision(Node *node)
{
}

float Node::get_left()
{
    return get_global_position().x - (collider.w / 2.0);
}

float Node::get_right()
{
    return get_global_position().x + (collider.w / 2.0);
}

float Node::get_top()
{
    return get_global_position().y - (collider.h / 2.0);
}

float Node::get_bottom()
{
    return get_global_position().y + (collider.h / 2.0);
}