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

    //�w��̍s��Vector4�ŕԂ��܂��iindex��0�`3�j
    Vector4 row(int index) const;
    //�w��̗��Vector4�ŕԂ��܂��iindex��0�`3�j
    Vector4 column(int index) const;
    //�s�񎮂�Ԃ��܂�
    float determinant() const;
    //�t�s���Ԃ��܂�
    Matrix4 inverse() const;
    //�]�u�s���Ԃ��܂�
    Matrix4 transpose() const;
    //�P�ʍs��Ɠ��������ǂ����𔻒肵�܂�
    bool isIdentity() const;
    ////��]�s�񂩂�N�H�[�^�j�I���֕ϊ����܂�
    //Quaternion ToQuaternion() const;


    //�s�񎮂�Ԃ��܂�
    static float Determinant(const Matrix4& m);
    //�t�s���Ԃ��܂�
    static Matrix4 Inverse(const Matrix4& m);
    //�]�u�s���Ԃ��܂�
    static Matrix4 Transpose(const Matrix4& m);

    ////��]�s�񂩂�N�H�[�^�j�I���֕ϊ����܂�
    //Quaternion ToQuaternion(const Matrix4& m);

    //�w�肵���x�N�g���g�嗦����g��k���s����쐬���܂�
    static Matrix4 Scale(const Vector3& v);
    //�w�肵��x, y, z�����ɂ��g��k���s����쐬���܂�
    static Matrix4 Scale(float x, float y, float z);
    //�e����Ɉ�l�Ɋg��k������g��k���s����쐬���܂�
    static Matrix4 Scale(float scale);

    //x���𒆐S�Ƃ�����]�s����쐬���܂�
    static Matrix4 RotationFromAxisX(float angle);
    //y���𒆐S�Ƃ�����]�s����쐬���܂�
    static Matrix4 RotationFromAxisY(float angle);
    //z���𒆐S�Ƃ�����]�s����쐬���܂�
    static Matrix4 RotationFromAxisZ(float angle);

    //�w�肵���x�N�g���ړ��ʂ��畽�s�ړ��s����쐬���܂�
    static Matrix4 Translation(const Vector3& velocity);
    //�w�肵��x, y, z�����ɂ�镽�s�ړ��s����쐬���܂�
    static Matrix4 Translation(float x, float y, float z);

    //�r���[�s����쐬���܂�
    static Matrix4 LookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector);

    //�������e�s����쐬���܂�
    static Matrix4 Perspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
    //����A�c����A�j�A�A�t�@�[ �r���[���ʋ����Ɋ�Â����������e�s����쐬���܂�
    static Matrix4 PerspectiveFieldOfView(float fov, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
    //���s���e�s����쐬���܂�
    static Matrix4 Orthographic(float width, float height, float zNearPlane, float zFarPlane);

    //UI�p�̓��e�s����쐬���܂��i�r���[�|�[�g�s��̋t�s��Ɠ����Ӗ��ł��j
    static Matrix4 UiProjection(float width, float height);

    //�r���[�|�[�g�s����쐬���܂�
    static Matrix4 Viewport(float width, float height);

    ////�n�_����I�_�܂ł��w���EaseType�ŕ�Ԃ��܂��it�̒l��0.0f�`1.0f�j
    //static Matrix4 Easing(const Matrix4& begin, const Matrix4& end, float t, EaseType easeType);


    Matrix4& operator *= (const Matrix4& matrix);

    bool operator == (const Matrix4& matrix) const;
    bool operator != (const Matrix4& matrix) const;
    Matrix4 operator * (const Matrix4& matrix) const;

    friend std::ostream& operator << (std::ostream& o, const Matrix4& matrix);
};