#ifndef UTIL_HPP
#define UTIL_HPP

using namespace std;

class Util {
public:
    // Constructor
    Util();

    // Destructor
    ~Util();

    // Other member functions and variables
    static bool pixel_out_of_bounds(int surface_width, int surface_height, int x, int y);

    /// @brief Moves a value toward a target value by a maximum delta. Does not go past the target.
    /// @param current The current value
    /// @param target The target value
    /// @param max_delta The maximum amount to move toward the target
    /// @return The new value
    static float move_toward(float current, float target, float max_delta);
};

#endif // UTIL_HPP
