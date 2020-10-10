#pragma once

#include<iostream>

struct Vector3;

struct Vector4 {
    float x, y, z, w;
    static const Vector4 zero;
    static const Vector4 one;

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(Vector3 v, float w);
    explicit Vector4(float num);

    //���K�������l��Ԃ��܂�
    Vector4 normalized() const;

    //�x�N�g���̒�����Ԃ��܂�
    float length() const;

    //�x�N�g���̒�����2���Ԃ��܂�
    float lengthSquared() const;

    //��Βl��Ԃ��܂�
    static Vector4 Abs(const Vector4& v);

    //�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l��Ԃ��܂�
    static Vector4 Clamp(const Vector4& v, const Vector4& min, const Vector4& max);

    //2�̃x�N�g���̊Ԃ̋������v�Z���܂�
    static float Distance(const Vector4& v1, const Vector4& v2);

    //2�̃x�N�g���̊Ԃ̋�����2����v�Z���܂�
    static float DistanceSquared(const Vector4& v1, const Vector4& v2);

    //2�̃x�N�g���̓��ς��v�Z���܂�
    static float Dot(const Vector4& v1, const Vector4& v2);

    //���K�������l��Ԃ��܂�
    static Vector4 Normalize(const Vector4& v);

    Vector4 operator +() const;
    Vector4 operator -() const;

    bool operator == (const Vector4& v) const;
    bool operator != (const Vector4& v) const;

    Vector4 operator + (const Vector4& v) const;
    Vector4 operator - (const Vector4& v) const;
    Vector4 operator * (float s) const;
    Vector4 operator / (float s) const;

    Vector4& operator += (const Vector4& v);
    Vector4& operator -= (const Vector4& v);
    Vector4& operator *= (float s);
    Vector4& operator /= (float s);

    friend Vector4 operator * (float s, const Vector4& v);
    friend Vector4 operator / (float s, const Vector4& v);
    friend std::ostream& operator << (std::ostream& o, const Vector4& v);
};