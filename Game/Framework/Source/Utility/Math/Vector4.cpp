#include"Vector4.h"
#include"Vector3.h"
#include"Mathf.h"
#include <iomanip>

const Vector4 Vector4::zero = { 0.0f, 0.0f, 0.0f, 0.0f };
const Vector4 Vector4::one = { 1.0f, 1.0f, 1.0f, 1.0f };

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{}

Vector4::Vector4(float num) : x(num), y(num), z(num), w(num)
{}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{}

Vector4::Vector4(Vector3 v, float w) : x(v.x), y(v.y), z(v.z), w(w)
{}

Vector4 Vector4::normalized()const
{
	float l = length();
	if (l == 0)return Vector4::zero;
	return { x / l, y / l, z / l, z / l };
}

float Vector4::length() const
{
	return mathf::Sqrt(lengthSquared());
}

float Vector4::lengthSquared() const
{
	return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Abs(const Vector4& v)
{
	return{ mathf::Abs(v.x),mathf::Abs(v.y),mathf::Abs(v.z), mathf::Abs(v.w) };
}

Vector4 Vector4::Clamp(const Vector4 & v, const Vector4 & min, const Vector4 & max)
{
	return { mathf::Clamp(v.x, min.x, max.x), mathf::Clamp(v.y, min.y, max.y), mathf::Clamp(v.z, min.z, max.z), mathf::Clamp(v.w, min.w, max.w) };
}

float Vector4::Distance(const Vector4 & v1, const Vector4 & v2)
{
	return (v1 - v2).length();
}

float Vector4::DistanceSquared(const Vector4 & v1, const Vector4 & v2)
{
	return (v1 - v2).lengthSquared();
}

float Vector4::Dot(const Vector4 & v1, const Vector4 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vector4 Vector4::Normalize(const Vector4 & v)
{
	return v.normalized();
}

Vector4 Vector4::operator+() const
{
	return *this;
}

Vector4 Vector4::operator-() const
{
	return { -x, -y, -z, -w };
}

bool Vector4::operator==(const Vector4 & v) const
{
	return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
}

bool Vector4::operator!=(const Vector4 & v) const
{
	return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
}

Vector4 Vector4::operator+(const Vector4 & v) const
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Vector4 Vector4::operator-(const Vector4 & v) const
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Vector4 Vector4::operator*(float s) const
{
	return { x * s, y * s, z * s, w * s };
}

Vector4 Vector4::operator/(float s) const
{
	if (s == 0)return *this;
	return { x / s, y / s, z / s, w / s };
}

Vector4 & Vector4::operator+=(const Vector4 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4 & Vector4::operator-=(const Vector4 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4 & Vector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vector4 & Vector4::operator/=(float s)
{
	if (s == 0)return *this;
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

Vector4 operator*(float s, const Vector4 & v)
{
	return { v.x * s, v.y * s, v.z * s, v.w * s };
}

Vector4 operator/(float s, const Vector4 & v)
{
	if (s == 0)return v;
	return { v.x / s, v.y / s, v.z / s, v.w / s };
}

std::ostream & operator<<(std::ostream & o, const Vector4 & v)
{
	return o /*<< std::fixed << std::setprecision(1)*/ << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
}