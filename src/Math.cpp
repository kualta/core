#include <core/Math.h>
#include <core/Vector.h>
#include <core/Matrix.h>
#include <cmath>


namespace core {

const float Math::PI = 4.0f * atan(1.0f);
const float Math::TWO_PI = 2.0f * PI;
const float Math::TAU = 2.0f * PI;
const float Math::HALF_PI = 0.5f * PI;
const float Math::LOG2 = std::log(2.0f);

Matrix4 Math::MatrixTranslation(const Vector3 &vec) {

    Matrix4 mat = Matrix4::identity;

    mat[0][3] = vec.x;
    mat[1][3] = vec.y;
    mat[2][3] = vec.z;
    mat[3][3] = 1.0f;

    return mat;
}

Matrix4 Math::MatrixRotationXYZ(float rotX, float rotY, float rotZ) {

    Matrix4 mat = Matrix4::zero;

    const float sx = sin(rotX);
    const float cx = cos(rotX);
    const float sy = sin(rotY);
    const float cy = cos(rotY);
    const float sz = sin(rotZ);
    const float cz = cos(rotZ);

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

} // namespace