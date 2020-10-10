#include"Matrix4.h"
#include"Mathf.h"
#include"Vector3.h"
#include"Vector4.h"

const Matrix4 Matrix4::zero = { { 0.0f, 0.0f, 0.0f, 0.0f },
                                { 0.0f, 0.0f, 0.0f, 0.0f },
                                { 0.0f, 0.0f, 0.0f, 0.0f },
                                { 0.0f, 0.0f, 0.0f, 0.0f } };

const Matrix4 Matrix4::identity = { { 1.0f, 0.0f, 0.0f, 0.0f },
                                    { 0.0f, 1.0f, 0.0f, 0.0f },
                                    { 0.0f, 0.0f, 1.0f, 0.0f },
                                    { 0.0f, 0.0f, 0.0f, 1.0f } };

Matrix4::Matrix4()
    : m{ {1.0f, 0.0f, 0.0f, 0.0f},
       {0.0f, 1.0f, 0.0f, 0.0f},
       {0.0f, 0.0f, 1.0f, 0.0f},
       {0.0f, 0.0f, 0.0f, 1.0f} } {}

Matrix4::Matrix4(Vector4 r1, Vector4 r2, Vector4 r3, Vector4 r4)
    : m{ {r1.x, r1.y, r1.z, r1.w},
       {r2.x, r2.y, r2.z, r2.w},
       {r3.x, r3.y, r3.z, r3.w},
       {r4.x, r4.y, r4.z, r4.w} } {}

Matrix4::Matrix4(
    float m11, float m12, float m13, float m14,
    float m21, float m22, float m23, float m24,
    float m31, float m32, float m33, float m34,
    float m41, float m42, float m43, float m44) :
    m{ {m11, m12, m13, m14},
       {m21, m22, m23, m24},
       {m31, m32, m33, m34},
       {m41, m42, m43, m44}, } {}

Vector4 Matrix4::row(int index) const {
    return Vector4(m[index][0], m[index][1], m[index][2], m[index][3]);
}

Vector4 Matrix4::column(int index) const {
    return Vector4(m[0][index], m[1][index], m[2][index], m[3][index]);
}

float Matrix4::determinant() const {
    float buffer = 0.0f;
    float matrix[4][4];
    std::memcpy(matrix, m, sizeof(m));

    //上三角行列を作成
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i >= j) continue;

            buffer = matrix[j][i] / matrix[i][i];

            for (int k = 0; k < 4; k++) {
                matrix[j][k] -= matrix[i][k] * buffer;
            }
        }
    }

    float det = 1.0f;

    //対角部分の積
    for (int i = 0; i < 4; i++) {
        det *= matrix[i][i];
    }

    return det;
}

Matrix4 Matrix4::inverse() const {
    float determinant = Matrix4::determinant();
    if (determinant == 0)return Matrix4::zero;
    //Assert(determinant != 0, "この行列には逆行列が存在しません");

    //掃き出し法で実装
    float buffer = 0.0f;
    float matrix[4][4];
    std::memcpy(matrix, m, sizeof(m));

    Matrix4 inverse = Matrix4::identity;

    for (int i = 0; i < 4; ++i) {
        buffer = 1 / matrix[i][i];
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] *= buffer;
            inverse.m[i][j] *= buffer;
        }

        for (int j = 0; j < 4; ++j) {
            if (i == j) continue;
            buffer = matrix[j][i];

            for (int k = 0; k < 4; ++k) {
                matrix[j][k] -= matrix[i][k] * buffer;
                inverse.m[j][k] -= inverse.m[i][k] * buffer;
            }
        }
    }

    return inverse;
}

Matrix4 Matrix4::transpose() const {
    return { m[0][0], m[1][0], m[2][0], m[3][0],
             m[0][1], m[1][1], m[2][1], m[3][1],
             m[0][2], m[1][2], m[2][2], m[3][2],
             m[0][3], m[1][3], m[2][3], m[3][3] };
}

bool Matrix4::isIdentity() const {
    return (*this) == Matrix4::identity;
}

float Matrix4::Determinant(const Matrix4 & m) {
    return m.determinant();
}

Matrix4 Matrix4::Inverse(const Matrix4 & m) {
    return m.inverse();
}

Matrix4 Matrix4::Transpose(const Matrix4 & m) {
    return m.transpose();
}

Matrix4 Matrix4::Scale(const Vector3 & v) {
    Matrix4 result = identity;
    result.m[0][0] = v.x;
    result.m[1][1] = v.y;
    result.m[2][2] = v.z;
    return result;
}

Matrix4 Matrix4::Scale(float x, float y, float z) {
    Matrix4 result = identity;
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    return result;
}

Matrix4 Matrix4::Scale(float scale) {
    Matrix4 result = identity;
    result.m[0][0] = scale;
    result.m[1][1] = scale;
    result.m[2][2] = scale;
    return result;
}

Matrix4 Matrix4::RotationFromAxisX(float angle) {
    Matrix4 result = identity;
    result.m[1][1] = mathf::Cos(angle);
    result.m[1][2] = mathf::Sin(angle);
    result.m[2][1] = -mathf::Sin(angle);
    result.m[2][2] = mathf::Cos(angle);
    return result;
}

Matrix4 Matrix4::RotationFromAxisY(float angle) {
    Matrix4 result = identity;
    result.m[0][0] = mathf::Cos(angle);
    result.m[0][2] = -mathf::Sin(angle);
    result.m[2][0] = mathf::Sin(angle);
    result.m[2][2] = mathf::Cos(angle);
    return result;
}

Matrix4 Matrix4::RotationFromAxisZ(float angle) {
    Matrix4 result = identity;
    result.m[0][0] = mathf::Cos(angle);
    result.m[0][1] = mathf::Sin(angle);
    result.m[1][0] = -mathf::Sin(angle);
    result.m[1][1] = mathf::Cos(angle);
    return result;
}

Matrix4 Matrix4::Translation(const Vector3 & velocity) {
    Matrix4 result = identity;
    result.m[3][0] = velocity.x;
    result.m[3][1] = velocity.y;
    result.m[3][2] = velocity.z;
    return result;
}

Matrix4 Matrix4::Translation(float x, float y, float z) {
    Matrix4 result = identity;
    result.m[3][0] = x;
    result.m[3][1] = y;
    result.m[3][2] = z;
    return result;
}

Matrix4 Matrix4::LookAt(const Vector3 & cameraPosition, const Vector3 & cameraTarget, const Vector3 & cameraUpVector) {
    //Z方向のベクトルを求める（カメラの正面方向）
    Vector3 axisZ = (cameraTarget - cameraPosition).normalized();

    //X方向のベクトルを求める（カメラの右方向）
    Vector3 axisX = Vector3::Cross(cameraUpVector, axisZ).normalized();

    //Y方向のベクトルを求める（カメラの上方向）
    Vector3 axisY = Vector3::Cross(axisZ, axisX);

    Matrix4 result = identity;
    result.m[0][0] = axisX.x; result.m[0][1] = axisY.x;	result.m[0][2] = axisZ.x;
    result.m[1][0] = axisX.y; result.m[1][1] = axisY.y;	result.m[1][2] = axisZ.y;
    result.m[2][0] = axisX.z; result.m[2][1] = axisY.z;	result.m[2][2] = axisZ.z;
    result.m[3][0] = Vector3::Dot(-cameraPosition, axisX); result.m[3][1] = Vector3::Dot(-cameraPosition, axisY);  result.m[3][2] = Vector3::Dot(-cameraPosition, axisZ);

    return result;
}

Matrix4 Matrix4::Perspective(float width, float height, float nearPlaneDistance, float farPlaneDistance) {
    float scaleX = 2.0f * nearPlaneDistance / width;
    float scaleY = 2.0f * nearPlaneDistance / height;
    float scaleZ = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
    float transZ = nearPlaneDistance * farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

    Matrix4 result = zero;
    result.m[0][0] = scaleX;
    result.m[1][1] = scaleY;
    result.m[2][2] = scaleZ;
    result.m[2][3] = 1.0f;
    result.m[3][2] = transZ;

    return result;
}

Matrix4 Matrix4::PerspectiveFieldOfView(float fov, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) {
    float scaleY = 1.0f / mathf::Tan(fov / 2.0f);
    float scaleX = scaleY / aspectRatio;
    float scaleZ = 1.0f / (farPlaneDistance - nearPlaneDistance) * farPlaneDistance;
    float transZ = -nearPlaneDistance / (farPlaneDistance - nearPlaneDistance) * farPlaneDistance;

    Matrix4 result = zero;
    result.m[0][0] = scaleX;
    result.m[1][1] = scaleY;
    result.m[2][2] = scaleZ;
    result.m[2][3] = 1.0f;
    result.m[3][2] = transZ;

    return result;
}

Matrix4 Matrix4::Orthographic(float width, float height, float zNearPlane, float zFarPlane) {
    float scaleX = 2.0f / width;
    float scaleY = 2.0f / height;
    float scaleZ = 1.0f / (zFarPlane - zNearPlane);
    float transZ = zNearPlane / (zNearPlane - zFarPlane);

    Matrix4 result = zero;
    result.m[0][0] = scaleX;
    result.m[1][1] = scaleY;
    result.m[2][2] = scaleZ;
    result.m[3][2] = transZ;
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4 Matrix4::UiProjection(float width, float height) {
    float scaleX = 2.0f / width;
    float scaleY = 2.0f / height;

    Matrix4 result = zero;
    result.m[0][0] = scaleX;
    result.m[1][1] = -scaleY;
    result.m[2][2] = 1.0f;
    result.m[3][0] = -1.0f;
    result.m[3][1] = 1.0f;
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4 Matrix4::Viewport(float width, float height) {
    float x = width / 2.0f;
    float y = height / 2.0f;

    Matrix4 result = zero;
    result.m[0][0] = x;
    result.m[1][1] = -y;
    result.m[2][2] = 1.0f;
    result.m[3][0] = x;
    result.m[3][1] = y;
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4 & Matrix4::operator*=(const Matrix4 & matrix) {
    Matrix4 result = Matrix4::zero;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * matrix.m[k][j];
            }
        }
    }

    *this = result;
    return *this;
}

bool Matrix4::operator==(const Matrix4 & matrix) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; i < 4; ++i) {
            if (m[i][j] != matrix.m[i][j]) return false;
        }
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4 & matrix) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; i < 4; ++i) {
            if (m[i][j] != matrix.m[i][j]) return true;
        }
    }
    return false;
}

Matrix4 Matrix4::operator*(const Matrix4 & matrix) const {
    Matrix4 result = Matrix4::zero;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * matrix.m[k][j];
            }
        }
    }

    return result;
}

std::ostream & operator<<(std::ostream & o, const Matrix4 & matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            o /*<< std::fixed << std::setprecision(1)*/ << matrix.m[i][j] << ", ";
        }
        o << "\n";
    }

    return o;
}