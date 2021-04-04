#include <core/Matrix.h>


namespace core {


template<int cols, int rows, typename T>
Matrix3 Matrix<cols, rows, T>::Translate(const Vector3 &v) {

}
const Matrix3 Matrix3::zero(
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,);
static const Matrix3 Matrix3::identity(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
    0, 0, 0,);
template<int cols, int rows, typename T>
Matrix4 Matrix<cols, rows, T>::Translate(const Vector4 &v) {

}

const Matrix4 Matrix4::zero(
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0 );
static const Matrix4 Matrix4::identity(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 );

} // namespace