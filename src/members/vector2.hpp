#ifndef VECTOR2_HPP
#define VECTOR2_HPP

using namespace std;

class Vector2 {
public:
    // Constructor
    Vector2(float x = 0, float y = 0);

    // Destructor
    ~Vector2();

    float x;
    float y;

    /// @brief Returns a copy of the vector rotated by the given degrees
    /// @param degrees The degrees to rotate the vector
    /// @return A copy of the vector rotated by the given degrees
    Vector2 rotated(float degrees);

    /// @brief Returns the length of the vector
    /// @return The length of the vector
    float length();

    /// @brief Returns a normalized copy of the vector
    /// @return A normalized copy of the vector
    Vector2 normalized();

    /// @brief Gets direction from this vector to the given target
    /// @param target The target vector
    /// @return The normalized vector direction to the given target
    Vector2 direction_to(Vector2 target);

    /// @brief Get angle of this vector in degrees
    /// @return The angle of this vector in degrees
    double angle();
};

#endif // Vector2_HPP
