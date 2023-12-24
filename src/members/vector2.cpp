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

float Vector2::length() {
    return sqrt((x * x) + (y * y));
}

Vector2 Vector2::normalized() {
    // Could be faster potentially with fast inverse square root
    float length = this->length();
    return Vector2(x / length, y / length);
}

Vector2 Vector2::direction_to(Vector2 target) {
    Vector2 direction = Vector2(target.x - x, target.y - y);
    return direction.normalized();
}

double Vector2::angle() {
    return atan2(y, x) * (180 / M_PI);
}