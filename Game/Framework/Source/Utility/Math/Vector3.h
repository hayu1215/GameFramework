#pragma once

#include<iostream>

struct Vector3
{
	float x, y, z;
	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;

	Vector3();
	Vector3(float x, float y, float z);
	explicit Vector3(float num);

	//正規化した値を返します
	Vector3 normalized() const;

	//ベクトルの長さを返します
	float length() const;

	//ベクトルの長さの2乗を返します
	float lengthSquared() const;

	//絶対値を返します
	static Vector3 Abs(const Vector3& v);

	//最小値と最大値の範囲内に収めた値を返します
	static Vector3 Clamp(const Vector3& v, const Vector3& min, const Vector3& max);

	//2つのベクトルの外積を計算します
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	//2つのベクトルの間の距離を計算します
	static float Distance(const Vector3& v1, const Vector3& v2);

	//2つのベクトルの間の距離の2乗を計算します
	static float DistanceSquared(const Vector3& v1, const Vector3& v2);

	//2つのベクトルの内積を計算します
	static float Dot(const Vector3& v1, const Vector3& v2);

	//正規化した値を返します
	static Vector3 Normalize(const Vector3& v);

	////行列を用いて座標を変換します
	//Vector3 Transform(const Vector3& v, const Matrix4& m);

	////行列を用いて座標を変換します（拡大縮小と回転のみ）
	//Vector3 TransformNormal(const Vector3& v, const Matrix4& m);

	////クォータニオンを用いて座標を変換します
	//Vector3 TransformQuaternion(const Vector3& v, const Quaternion& q);

	Vector3 operator +() const;
	Vector3 operator -() const;

	bool operator == (const Vector3& v) const;
	bool operator != (const Vector3& v) const;

	Vector3 operator + (const Vector3& v) const;
	Vector3 operator - (const Vector3& v) const;
	Vector3 operator * (float s) const;
	Vector3 operator / (float s) const;

	Vector3& operator += (const Vector3& v);
	Vector3& operator -= (const Vector3& v);
	Vector3& operator *= (float s);
	Vector3& operator /= (float s);

	friend Vector3 operator * (float s, const Vector3& v);
	friend Vector3 operator / (float s, const Vector3& v);
	friend std::ostream& operator << (std::ostream& o, const Vector3& v);
};