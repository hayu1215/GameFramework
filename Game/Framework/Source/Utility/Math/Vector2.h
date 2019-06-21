#pragma once

#include<iostream>

struct Vector2
{
	float x, y;
	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 left;
	static const Vector2 right;

	Vector2();
	Vector2(float x, float y);
	explicit Vector2(float num);

	//正規化した値を返します
	Vector2 normalized() const;

	//ベクトルの長さを返します
	float length() const;

	//ベクトルの長さの2乗を返します
	float lengthSquared() const;

	//絶対値を返します
	static Vector2 Abs(const Vector2& v);

	//最小値と最大値の範囲内に収めた値を返します
	static Vector2 Clamp(const Vector2& v, const Vector2& min, const Vector2& max);

	//2つのベクトルの外積を計算します
	static float Cross(const Vector2& v1, const Vector2& v2);

	//2つのベクトルの間の距離を計算します
	static float Distance(const Vector2& v1, const Vector2& v2);

	//2つのベクトルの間の距離の2乗を計算します
	static float DistanceSquared(const Vector2& v1, const Vector2& v2);

	//2つのベクトルの内積を計算します
	static float Dot(const Vector2& v1, const Vector2& v2);

	//正規化した値を返します
	static Vector2 Normalize(const Vector2& v);

	Vector2 operator +() const;
	Vector2 operator -() const;

	bool operator == (const Vector2& v) const;
	bool operator != (const Vector2& v) const;

	Vector2 operator + (const Vector2& v) const;
	Vector2 operator - (const Vector2& v) const;
	Vector2 operator * (float s) const;
	Vector2 operator / (float s) const;

	Vector2& operator += (const Vector2& v);
	Vector2& operator -= (const Vector2& v);
	Vector2& operator *= (float s);
	Vector2& operator /= (float s);

	friend Vector2 operator * (float s, const Vector2& v);
	friend Vector2 operator / (float s, const Vector2& v);
	friend std::ostream& operator << (std::ostream& o, const Vector2& v);
};