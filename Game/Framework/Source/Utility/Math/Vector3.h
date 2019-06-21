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

	//���K�������l��Ԃ��܂�
	Vector3 normalized() const;

	//�x�N�g���̒�����Ԃ��܂�
	float length() const;

	//�x�N�g���̒�����2���Ԃ��܂�
	float lengthSquared() const;

	//��Βl��Ԃ��܂�
	static Vector3 Abs(const Vector3& v);

	//�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l��Ԃ��܂�
	static Vector3 Clamp(const Vector3& v, const Vector3& min, const Vector3& max);

	//2�̃x�N�g���̊O�ς��v�Z���܂�
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	//2�̃x�N�g���̊Ԃ̋������v�Z���܂�
	static float Distance(const Vector3& v1, const Vector3& v2);

	//2�̃x�N�g���̊Ԃ̋�����2����v�Z���܂�
	static float DistanceSquared(const Vector3& v1, const Vector3& v2);

	//2�̃x�N�g���̓��ς��v�Z���܂�
	static float Dot(const Vector3& v1, const Vector3& v2);

	//���K�������l��Ԃ��܂�
	static Vector3 Normalize(const Vector3& v);

	////�s���p���č��W��ϊ����܂�
	//Vector3 Transform(const Vector3& v, const Matrix4& m);

	////�s���p���č��W��ϊ����܂��i�g��k���Ɖ�]�̂݁j
	//Vector3 TransformNormal(const Vector3& v, const Matrix4& m);

	////�N�H�[�^�j�I����p���č��W��ϊ����܂�
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