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

    //正規化した値を返します
    Vector4 normalized() const;

    //ベクトルの長さを返します
    float length() const;

    //ベクトルの長さの2乗を返します
    float lengthSquared() const;

    //絶対値を返します
    static Vector4 Abs(const Vector4& v);

    //最小値と最大値の範囲内に収めた値を返します
    static Vector4 Clamp(const Vector4& v, const Vector4& min, const Vector4& max);

    //2つのベクトルの間の距離を計算します
    static float Distance(const Vector4& v1, const Vector4& v2);

    //2つのベクトルの間の距離の2乗を計算します
    static float DistanceSquared(const Vector4& v1, const Vector4& v2);

    //2つのベクトルの内積を計算します
    static float Dot(const Vector4& v1, const Vector4& v2);

    //正規化した値を返します
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