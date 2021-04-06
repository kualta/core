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
    0, 0, 0);
const Matrix3 Matrix3::identity(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1);

const Matrix4 Matrix4::zero(
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0 );
const Matrix4 Matrix4::identity(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 );

} // namespace