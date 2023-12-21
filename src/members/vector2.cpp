#include "vector2.hpp"


Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2::~Vector2() {
}

Vector2 Vector2::rotated(float radians) {
    float x2 = x * cos(radians) - y * sin(radians);
    float y2 = x * sin(radians) + y * cos(radians);

    return Vector2(x2, y2);
}