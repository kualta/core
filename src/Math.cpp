#include <core/Math.h>
#include <core/Primitive.h>
#include <core/Vector.h>
#include <core/Matrix.h>

#include <cmath>


namespace core {

const float Math::PI = 4.0f * atan(1.0f);
const float Math::TWO_PI = 2.0f * PI;
const float Math::TAU = 2.0f * PI;
const float Math::HALF_PI = 0.5f * PI;
const float Math::LOG2 = std::log(2.0f);

Matrix4 Math::TranslationMatrix(const Vector3 &pos) {

    Matrix4 mat = Matrix4::identity;

    mat[3][0] = pos.x;
    mat[3][1] = pos.y;
    mat[3][2] = pos.z;

    return mat;
}
Matrix4 Math::EulerRotationMatrix(const Vector3& euler) {

    Matrix4 mat = Matrix4::zero;

    const float sx = std::sin(euler.x);
    const float cx = std::cos(euler.x);
    const float sy = std::sin(euler.y);
    const float cy = std::cos(euler.y);
    const float sz = std::sin(euler.z);
    const float cz = std::cos(euler.z);

    mat[0][0] = cy*cz;
    mat[0][1] = -cy*sz;
    mat[0][2] = sy;

    mat[1][0] = cz*sx*sy + cx*sz;
    mat[1][1] = cx*cz - sx*sy*sz;
    mat[1][2] = -cy*sx;

    mat[2][0] = -cx*cz*sy + sx*sz;
    mat[2][1] = cz*sx + cx*sy*sz;
    mat[2][2] = cx*cy;

    mat[3][3] = 1.0f;

    return mat;
}
Matrix4 Math::ScaleMatrix(Vector3 scale) {

    Matrix4 mtx = Matrix4::zero;

    mtx[0][0] = scale.x;
    mtx[1][1] = scale.y;
    mtx[2][2] = scale.z;
    mtx[3][3] = 1.0f;

    return mtx;
}
Vector3 Math::Cross(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3 (
                lhs.y*rhs.z - lhs.z*rhs.y,
                lhs.z*rhs.x - lhs.x*rhs.z,
                lhs.x*rhs.y - lhs.y*rhs.x);
}
Vector3 Math::Normalize(const Vector3& vec) {
    const float invLen = Math::QRSqrt(Dot(vec, vec));
    if ( invLen == std::numeric_limits<float>::infinity() ) {
        return Vector3::zero;
    } else {
        return vec * invLen;
    }
}
Vector3 Math::Normalize(const Vector3&& vec) {
    const float invLen = Math::QRSqrt(Dot(vec, vec));
    if ( invLen == std::numeric_limits<float>::infinity() ) {
        return Vector3::zero;
    } else {
        return vec * invLen;
    }
}
Matrix4 Math::LookAtMatrix(const Vector3 &pos, const Vector3 &lookAt, const Vector3 &worldUp) {
    /*
      *   [         right.x          forward.x          up.x  0 ]
      *   [         right.y          forward.y          up.y  0 ]
      *   [         right.z          forward.z          up.z  0 ]
      *   [ dot(right,-pos)  dot(forward,-pos)  dot(up,-pos)  1 ]
     */
    // Core uses left-handed coordinate system
    const Vector3 forward = Math::Normalize(lookAt - pos);
    const Vector3 right   = Math::Normalize(Math::Cross(worldUp, forward));
    const Vector3 up      = Math::Cross(forward, right);

    Matrix4 mtx = Matrix4::zero;

    mtx[0][0] = right.x;
    mtx[0][1] = up.x;
    mtx[0][2] = forward.x;

    mtx[1][0] = right.y;
    mtx[1][1] = up.y;
    mtx[1][2] = forward.y;

    mtx[2][0] = right.z;
    mtx[2][1] = up.z;
    mtx[2][2] = forward.z;

    mtx[3][0] = -Math::Dot(right, pos);
    mtx[3][1] = -Math::Dot(up, pos);
    mtx[3][2] = -Math::Dot(forward, pos);

    mtx[3][3] = 1.0f;

    return mtx;
}
Matrix4 Math::ProjectionMatrix(float top, float bottom, float left, float right, float near, float far, bool hmgNdc) {
    const float invDiffRl = 1.0f / (right - left);
    const float invDiffTb = 1.0f / (top - bottom);
    const float width  = 2.0f * near * invDiffRl;
    const float height = 2.0f * near * invDiffTb;
    const float x      = (right + left) * invDiffRl;
    const float y      = (top + bottom) * invDiffTb;
    return ProjectionMatrix(Rect{ x, y, width, height }, near, far, hmgNdc);
}
Matrix4 Math::ProjectionMatrix(float fovY, float aspect, float near, float far, bool hmgNdc) {
    const float height = 1.0f / Math::Tan(Math::DegreesToRadians(Degree(fovY * 0.5f)));
    const float width  = height * 1.0f / aspect;
    return ProjectionMatrix(Rect { 0.0f, 0.0f, width, height }, near, far, hmgNdc);
}
Matrix4 Math::ProjectionMatrix(Rect rect, float near, float far, bool hmgNdc) {
    const float diff = far - near;
    const float a = hmgNdc ? (far + near) / diff : far / diff;
    const float b = hmgNdc ? (2.0f * far * near) / diff : near * a;

    Matrix4 mtx = Matrix4::zero;

    mtx[0][0] = rect.w;
    mtx[1][1] = rect.h;
    mtx[2][0] = -rect.x;
    mtx[2][1] = -rect.y;
    mtx[2][2] = a;
    mtx[2][3] = 1.0f;
    mtx[3][2] = -b;

    return mtx;
}

} // namespace