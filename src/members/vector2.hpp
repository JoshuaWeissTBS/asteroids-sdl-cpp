#ifndef VECTOR2_HPP
#define VECTOR2_HPP

using namespace std;

class Vector2 {
public:
    // Constructor
    Vector2(double x = 0, double y = 0);

    // Destructor
    ~Vector2();

    double x;
    double y;

    /// @brief Returns a copy of the vector rotated by the given degrees
    /// @param degrees The degrees to rotate the vector
    /// @return A copy of the vector rotated by the given degrees
    Vector2 rotated(double degrees);

    /// @brief Returns the length of the vector
    /// @return The length of the vector
    double length();

    /// @brief Returns a normalized copy of the vector
    /// @return A normalized copy of the vector
    Vector2 normalized();

    /// @brief Gets direction from this vector to the given target
    /// @param target The target vector
    /// @return The normalized vector direction to the given target
    Vector2 direction_to(Vector2 target);

    /// @brief Gets the distance between this vector and the given target
    /// @param target The target vector
    /// @return The distance between this vector and the given target
    double distance_to(Vector2 target);

    /// @brief Get angle of this vector in degrees
    /// @return The angle of this vector in degrees
    double angle();

    /// @brief Returns a copy of the vector rotated by the given degrees around the given anchor
    /// @param degrees The degrees to rotate the vector
    /// @param anchor The anchor to rotate the vector around
    /// @return A copy of the vector rotated by the given degrees around the given anchor
    Vector2 rotated_around_anchor(double degrees, Vector2 anchor);

    /// @brief Override multiplication operator to multiply a vector by a scalar
    /// @param scalar The scalar to multiply the vector by
    /// @return The multiplied vector
    Vector2 operator*(double scalar);

    /// @brief Override division operator to divide a vector by a scalar
    /// @param scalar The scalar to divide the vector by
    /// @return The divided vector
    Vector2 operator/(double scalar);

    /// @brief Override addition operator to add a scalar to a vector
    /// @param scalar The scalar to add to the vector
    /// @return The added vector
    Vector2 operator+(double scalar);

    /// @brief Override subtraction operator to subtract a scalar from a vector
    /// @param scalar The scalar to subtract from the vector
    /// @return The subtracted vector
    Vector2 operator-(double scalar);

    /// @brief Override addition operator to add two vectors
    /// @param other The other vector to add
    /// @return The added vector
    Vector2 operator+(Vector2 other);

    /// @brief Override subtraction operator to subtract two vectors
    /// @param other The other vector to subtract
    /// @return The subtracted vector
    Vector2 operator-(Vector2 other);

    /// @brief Override multiplication operator to multiply a vector by a vector
    /// @param other The other vector to multiply
    /// @return The multiplied vector
    Vector2 operator*(Vector2 other);

    /// @brief Override division operator to divide a vector by a vector
    /// @param other The other vector to divide
    /// @return The divided vector
    Vector2 operator/(Vector2 other);
};

#endif // Vector2_HPP
