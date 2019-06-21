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

	//���K�������l��Ԃ��܂�
	Vector2 normalized() const;

	//�x�N�g���̒�����Ԃ��܂�
	float length() const;

	//�x�N�g���̒�����2���Ԃ��܂�
	float lengthSquared() const;

	//��Βl��Ԃ��܂�
	static Vector2 Abs(const Vector2& v);

	//�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l��Ԃ��܂�
	static Vector2 Clamp(const Vector2& v, const Vector2& min, const Vector2& max);

	//2�̃x�N�g���̊O�ς��v�Z���܂�
	static float Cross(const Vector2& v1, const Vector2& v2);

	//2�̃x�N�g���̊Ԃ̋������v�Z���܂�
	static float Distance(const Vector2& v1, const Vector2& v2);

	//2�̃x�N�g���̊Ԃ̋�����2����v�Z���܂�
	static float DistanceSquared(const Vector2& v1, const Vector2& v2);

	//2�̃x�N�g���̓��ς��v�Z���܂�
	static float Dot(const Vector2& v1, const Vector2& v2);

	//���K�������l��Ԃ��܂�
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