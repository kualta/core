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
Matrix4 Math::TranslationMatrix(const Vector3 &vec) {

    Matrix4 mat = Matrix4::identity;

    mat[0][3] = vec.x;
    mat[1][3] = vec.y;
    mat[2][3] = vec.z;
    mat[3][3] = 1.0f;

    return mat;
}

} // namespace