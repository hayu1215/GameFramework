#pragma once

#include<iostream>

struct Vector3;
struct Vector4;

struct Matrix4 {
    float m[4][4];
    static const Matrix4 zero;
    static const Matrix4 identity;

    Matrix4();
    Matrix4(Vector4 r1, Vector4 r2, Vector4 r3, Vector4 r4);
    Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);

    //指定の行をVector4で返します（indexは0～3）
    Vector4 row(int index) const;
    //指定の列をVector4で返します（indexは0～3）
    Vector4 column(int index) const;
    //行列式を返します
    float determinant() const;
    //逆行列を返します
    Matrix4 inverse() const;
    //転置行列を返します
    Matrix4 transpose() const;
    //単位行列と等しいかどうかを判定します
    bool isIdentity() const;
    ////回転行列からクォータニオンへ変換します
    //Quaternion ToQuaternion() const;


    //行列式を返します
    static float Determinant(const Matrix4& m);
    //逆行列を返します
    static Matrix4 Inverse(const Matrix4& m);
    //転置行列を返します
    static Matrix4 Transpose(const Matrix4& m);

    ////回転行列からクォータニオンへ変換します
    //Quaternion ToQuaternion(const Matrix4& m);

    //指定したベクトル拡大率から拡大縮小行列を作成します
    static Matrix4 Scale(const Vector3& v);
    //指定したx, y, z成分による拡大縮小行列を作成します
    static Matrix4 Scale(float x, float y, float z);
    //各軸上に一様に拡大縮小する拡大縮小行列を作成します
    static Matrix4 Scale(float scale);

    //x軸を中心とした回転行列を作成します
    static Matrix4 RotationFromAxisX(float angle);
    //y軸を中心とした回転行列を作成します
    static Matrix4 RotationFromAxisY(float angle);
    //z軸を中心とした回転行列を作成します
    static Matrix4 RotationFromAxisZ(float angle);

    //指定したベクトル移動量から平行移動行列を作成します
    static Matrix4 Translation(const Vector3& velocity);
    //指定したx, y, z成分による平行移動行列を作成します
    static Matrix4 Translation(float x, float y, float z);

    //ビュー行列を作成します
    static Matrix4 LookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector);

    //透視投影行列を作成します
    static Matrix4 Perspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
    //視野、縦横比、ニア、ファー ビュー平面距離に基づいた透視投影行列を作成します
    static Matrix4 PerspectiveFieldOfView(float fov, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
    //平行投影行列を作成します
    static Matrix4 Orthographic(float width, float height, float zNearPlane, float zFarPlane);

    //UI用の投影行列を作成します（ビューポート行列の逆行列と同じ意味です）
    static Matrix4 UiProjection(float width, float height);

    //ビューポート行列を作成します
    static Matrix4 Viewport(float width, float height);

    ////始点から終点までを指定のEaseTypeで補間します（tの値は0.0f～1.0f）
    //static Matrix4 Easing(const Matrix4& begin, const Matrix4& end, float t, EaseType easeType);


    Matrix4& operator *= (const Matrix4& matrix);

    bool operator == (const Matrix4& matrix) const;
    bool operator != (const Matrix4& matrix) const;
    Matrix4 operator * (const Matrix4& matrix) const;

    friend std::ostream& operator << (std::ostream& o, const Matrix4& matrix);
};