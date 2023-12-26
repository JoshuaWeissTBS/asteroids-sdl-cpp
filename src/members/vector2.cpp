#include "vector2.hpp"
#include <cmath>

Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2::~Vector2() {
}

Vector2 Vector2::rotated(double radians) {
    double x2 = x * cos(radians) - y * sin(radians);
    double y2 = x * sin(radians) + y * cos(radians);

    return Vector2(x2, y2);
}

Vector2 Vector2::rotated_around_anchor(double radians, Vector2 anchor) {
    Vector2 translated = Vector2(x - anchor.x, y - anchor.y);
    Vector2 rotated = translated.rotated(radians);
    Vector2 translated_back = Vector2(rotated.x + anchor.x, rotated.y + anchor.y);
    return translated_back;
}

double Vector2::distance_to(Vector2 target) {
    return sqrt(pow(target.x - x, 2) + pow(target.y - y, 2));
}

double Vector2::length() {
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

Vector2 Vector2::operator+(double scalar) {
    return Vector2(x + scalar, y + scalar);
}

Vector2 Vector2::operator-(double scalar) {
    return Vector2(x - scalar, y - scalar);
}

Vector2 Vector2::operator*(double scalar) {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(double scalar) {
    return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator+(Vector2 other) {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(Vector2 other) {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(Vector2 other) {
    return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator/(Vector2 other) {
    return Vector2(x / other.x, y / other.y);
}
