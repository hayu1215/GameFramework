#include"Vector3.h"
#include"Matrix4.h"
#include<iomanip>
#include"Mathf.h"

const Vector3 Vector3::zero = { 0.0f, 0.0f, 0.0f };
const Vector3 Vector3::one = { 1.0f, 1.0f, 1.0f };

const Vector3 Vector3::forward = { 0.0f, 0.0f, 1.0f };
const Vector3 Vector3::back = { 0.0f, 0.0f, -1.0f };

const Vector3 Vector3::up = { 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::down = { 0.0f, -1.0f, 0.0f };
const Vector3 Vector3::left = { -1.0f, 0.0f, 0.0f };
const Vector3 Vector3::right = { 1.0f, 0.0f, 0.0f };

Vector3::Vector3()
    : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float num)
    : x(num), y(num), z(num) {}

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z) {}

Vector3 Vector3::normalized()const {
    float l = length();
    if (l == 0)return Vector3::zero;
    return { x / l, y / l, z / l };
}

float Vector3::length() const {
    return mathf::Sqrt(lengthSquared());
}

float Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

Vector3 Vector3::Abs(const Vector3& v) {
    return{ mathf::Abs(v.x),mathf::Abs(v.y),mathf::Abs(v.z) };
}

Vector3 Vector3::Clamp(const Vector3 & v, const Vector3 & min, const Vector3 & max) {
    return { mathf::Clamp(v.x, min.x, max.x), mathf::Clamp(v.y, min.y, max.y), mathf::Clamp(v.z, min.z, max.z) };
}

Vector3 Vector3::Cross(const Vector3 & v1, const Vector3 & v2) {
    return  { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

float Vector3::Distance(const Vector3 & v1, const Vector3 & v2) {
    return (v1 - v2).length();
}

float Vector3::DistanceSquared(const Vector3 & v1, const Vector3 & v2) {
    return (v1 - v2).lengthSquared();
}

float Vector3::Dot(const Vector3 & v1, const Vector3 & v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Normalize(const Vector3 & v) {
    return v.normalized();
}

//Vector3 Vector3_S::Normalize(const Vector3 & v)
//{
//	return v.Normalized();
//}
//
Vector3 Vector3::Transform(const Vector3 & v, const Matrix4 & m) {
    float x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    float y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    float z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];

    return { x, y, z };
}
//
//Vector3 Vector3_S::TransformNormal(const Vector3 & v, const Matrix4 & m)
//{
//	float x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
//	float y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
//	float z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
//
//	return { x, y, z };
//}
//
//Vector3 Vector3_S::TransformQuaternion(const Vector3 & v, const Quaternion & q)
//{
//	float x = q.y * v.z - q.z * v.y + q.w * v.x;
//	float y = q.z * v.x - q.x * v.z + q.w * v.y;
//	float z = q.x * v.y - q.y * v.x + q.w * v.z;
//	float w = -q.x * v.x - q.y * v.y - q.z * v.z;
//
//	float vx = y * -q.z + z * q.y - w * q.x + x * q.w;
//	float vy = z * -q.x + x * q.z - w * q.y + y * q.w;
//	float vz = x * -q.y + y * q.x - w * q.z + z * q.w;
//
//	return { vx, vy, vz };
//}

Vector3 Vector3::operator+() const {
    return *this;
}

Vector3 Vector3::operator-() const {
    return { -x, -y, -z };
}

bool Vector3::operator==(const Vector3 & v) const {
    return (x == v.x) && (y == v.y) && (z == v.z);
}

bool Vector3::operator!=(const Vector3 & v) const {
    return (x != v.x) || (y != v.y) || (z != v.z);
}

Vector3 Vector3::operator+(const Vector3 & v) const {
    return { x + v.x, y + v.y, z + v.z };
}

Vector3 Vector3::operator-(const Vector3 & v) const {
    return { x - v.x, y - v.y, z - v.z };
}

Vector3 Vector3::operator*(float s) const {
    return { x * s, y * s, z * s };
}

Vector3 Vector3::operator/(float s) const {
    if (s == 0)return *this;
    return { x / s, y / s, z / s };
}

Vector3 & Vector3::operator+=(const Vector3 & v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 & Vector3::operator-=(const Vector3 & v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3 & Vector3::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector3 & Vector3::operator/=(float s) {
    if (s == 0)return *this;
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

Vector3 operator*(float s, const Vector3 & v) {
    return { v.x * s, v.y * s, v.z * s };
}

Vector3 operator/(float s, const Vector3 & v) {
    if (s == 0)return v;
    return { v.x / s, v.y / s, v.z / s };
}

std::ostream & operator<<(std::ostream & o, const Vector3 & v) {
    return o /*<< std::fixed << std::setprecision(1)*/ << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}