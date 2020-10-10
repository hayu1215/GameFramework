#include"Vector2.h"
#include<iomanip>
#include"Mathf.h"

const Vector2 Vector2::zero = { 0.0f, 0.0f };
const Vector2 Vector2::one = { 1.0f, 1.0f };
const Vector2 Vector2::up = { 0.0f, 1.0f };
const Vector2 Vector2::down = { 0.0f, -1.0f };
const Vector2 Vector2::left = { -1.0f, 0.0f };
const Vector2 Vector2::right = { 1.0f, 0.0f };

Vector2::Vector2()
    : x(0.0f), y(0.0f) {}

Vector2::Vector2(float num)
    : x(num), y(num) {}

Vector2::Vector2(float x, float y)
    : x(x), y(y) {}

Vector2 Vector2::normalized()const {
    float l = length();
    if (l == 0)return Vector2::zero;
    return { x / l, y / l };
}

float Vector2::length() const {
    return mathf::Sqrt(lengthSquared());
}

float Vector2::lengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::Abs(const Vector2& v) {
    return{ mathf::Abs(v.x),mathf::Abs(v.y) };
}

Vector2 Vector2::Clamp(const Vector2 & v, const Vector2 & min, const Vector2 & max) {
    return { mathf::Clamp(v.x, min.x, max.x), mathf::Clamp(v.y, min.y, max.y) };
}

float Vector2::Cross(const Vector2 & v1, const Vector2 & v2) {
    return  v1.x * v2.y - v1.y * v2.x;
}

float Vector2::Distance(const Vector2 & v1, const Vector2 & v2) {
    return (v1 - v2).length();
}

float Vector2::DistanceSquared(const Vector2 & v1, const Vector2 & v2) {
    return (v1 - v2).lengthSquared();
}

float Vector2::Dot(const Vector2 & v1, const Vector2 & v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2 Vector2::Normalize(const Vector2 & v) {
    return v.normalized();
}

Vector2 Vector2::operator+() const {
    return *this;
}

Vector2 Vector2::operator-() const {
    return { -x, -y };
}

bool Vector2::operator==(const Vector2 & v) const {
    return (x == v.x) && (y == v.y);
}

bool Vector2::operator!=(const Vector2 & v) const {
    return (x != v.x) || (y != v.y);
}

Vector2 Vector2::operator+(const Vector2 & v) const {
    return { x + v.x, y + v.y };
}

Vector2 Vector2::operator-(const Vector2 & v) const {
    return { x - v.x, y - v.y };
}

Vector2 Vector2::operator*(float s) const {
    return { x * s, y * s };
}

Vector2 Vector2::operator/(float s) const {
    if (s == 0)return { x, y };
    return { x / s, y / s };
}

Vector2 & Vector2::operator+=(const Vector2 & v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2 & Vector2::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vector2 & Vector2::operator/=(float s) {
    if (s == 0)return *this;
    x /= s;
    y /= s;
    return *this;
}

Vector2 operator*(float s, const Vector2 & v) {
    return { v.x * s, v.y * s };
}

Vector2 operator/(float s, const Vector2 & v) {
    if (s == 0)return { v.x, v.y };
    return { v.x / s, v.y / s };
}

std::ostream & operator<<(std::ostream & o, const Vector2 & v) {
    return o /*<< std::fixed << std::setprecision(1)*/ << '(' << v.x << ", " << v.y << ')';
}