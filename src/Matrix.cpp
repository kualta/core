#include <core/Matrix.h>
#include "core/Vector.h"


namespace core {

template<int cols, int rows, typename T>
Matrix3 Matrix<cols, rows, T>::Translate(const Vector3 &vec) {

    Matrix3 mat = Matrix3::identity;

    mat[0][2] = vec.x;
    mat[1][2] = vec.y;
    mat[2][2] = vec.z;

    return mat;
}
template<int cols, int rows, typename T>
Matrix4 Matrix<cols, rows, T>::Translate(const Vector4 &vec) {

    Matrix4 mat = Matrix4::identity;

    mat[0][3] = vec.x;
    mat[1][3] = vec.y;
    mat[2][3] = vec.z;
    mat[3][3] = vec.w;

    return mat;
}

const Matrix3 Matrix3::zero(
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
    );
const Matrix3 Matrix3::identity(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
    );


const Matrix4 Matrix4::zero(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
        );
const Matrix4 Matrix4::identity(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        );

} // namespace

core::Matrix4 core::operator*(const core::Matrix4 &m, const core::Matrix4 &m2)
{
    core::Matrix4 r;

    r[0][0] = m[0][0] * m2[0][0] + m[0][1] * m2[1][0] + m[0][2] * m2[2][0] + m[0][3] * m2[3][0];
    r[0][1] = m[0][0] * m2[0][1] + m[0][1] * m2[1][1] + m[0][2] * m2[2][1] + m[0][3] * m2[3][1];
    r[0][2] = m[0][0] * m2[0][2] + m[0][1] * m2[1][2] + m[0][2] * m2[2][2] + m[0][3] * m2[3][2];
    r[0][3] = m[0][0] * m2[0][3] + m[0][1] * m2[1][3] + m[0][2] * m2[2][3] + m[0][3] * m2[3][3];

    r[1][0] = m[1][0] * m2[0][0] + m[1][1] * m2[1][0] + m[1][2] * m2[2][0] + m[1][3] * m2[3][0];
    r[1][1] = m[1][0] * m2[0][1] + m[1][1] * m2[1][1] + m[1][2] * m2[2][1] + m[1][3] * m2[3][1];
    r[1][2] = m[1][0] * m2[0][2] + m[1][1] * m2[1][2] + m[1][2] * m2[2][2] + m[1][3] * m2[3][2];
    r[1][3] = m[1][0] * m2[0][3] + m[1][1] * m2[1][3] + m[1][2] * m2[2][3] + m[1][3] * m2[3][3];

    r[2][0] = m[2][0] * m2[0][0] + m[2][1] * m2[1][0] + m[2][2] * m2[2][0] + m[2][3] * m2[3][0];
    r[2][1] = m[2][0] * m2[0][1] + m[2][1] * m2[1][1] + m[2][2] * m2[2][1] + m[2][3] * m2[3][1];
    r[2][2] = m[2][0] * m2[0][2] + m[2][1] * m2[1][2] + m[2][2] * m2[2][2] + m[2][3] * m2[3][2];
    r[2][3] = m[2][0] * m2[0][3] + m[2][1] * m2[1][3] + m[2][2] * m2[2][3] + m[2][3] * m2[3][3];

    r[3][0] = m[3][0] * m2[0][0] + m[3][1] * m2[1][0] + m[3][2] * m2[2][0] + m[3][3] * m2[3][0];
    r[3][1] = m[3][0] * m2[0][1] + m[3][1] * m2[1][1] + m[3][2] * m2[2][1] + m[3][3] * m2[3][1];
    r[3][2] = m[3][0] * m2[0][2] + m[3][1] * m2[1][2] + m[3][2] * m2[2][2] + m[3][3] * m2[3][2];
    r[3][3] = m[3][0] * m2[0][3] + m[3][1] * m2[1][3] + m[3][2] * m2[2][3] + m[3][3] * m2[3][3];

    return r;
}
