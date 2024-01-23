#ifndef UTIL_HPP
#define UTIL_HPP
#include <SDL2/SDL.h>
#include <unordered_map>
#include "node.hpp"

using namespace std;

class Util {
public:
    // Constructor
    Util();

    // Destructor
    ~Util();

    // Other member functions and variables
    static bool pixel_out_of_bounds(double surface_width, double surface_height, double x, double y);

    /// @brief Moves a value toward a target value by a maximum delta. Does not go past the target.
    /// @param current The current value
    /// @param target The target value
    /// @param max_delta The maximum amount to move toward the target
    /// @return The new value
    static double move_toward(double current, double target, double max_delta);

    /// @brief checks collision between two SDL_Rects
    /// @param a The first SDL_Rect
    /// @param b The second SDL_Rect
    /// @return true if the two rects are colliding, false otherwise
    static bool check_collision(SDL_FRect a, SDL_FRect b);

    /// @brief Converts degrees to radians
    /// @param degrees The degrees to convert
    /// @return The radians
    static double degrees_to_radians(double degrees);

    /// @brief Converts radians to degrees
    /// @param radians The radians to convert
    /// @return The degrees
    static double radians_to_degrees(double radians);

    /// @brief Clamps a value between a minimum and maximum value
    /// @param value The value to clamp
    /// @param min The minimum value
    /// @param max The maximum value
    static double clamp (double value, double min, double max);

    /// @brief Checks collisions between nodes and returns a vector of collided nodes. Sets collisions vector on each node.
    /// @param nodes The nodes to check collisions between
    /// @return A vector of collided nodes
    static void get_collisions(vector<Node*> nodes);
};

#endif // UTIL_HPP
