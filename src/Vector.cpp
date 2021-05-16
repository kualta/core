#include <core/Vector.h>
#include <core/Math.h>

namespace core {

// --------------- Vector3 ------------------
float Vector3::Length() const {
    return Math::Sqrt(Math::Dot(*this, *this));
}
Vector3 operator*(const Vector3 &vec, const float &num) {
    return Vector3(vec.x * num,
                   vec.y * num,
                   vec.z * num);
}
Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3(
            lhs.x - rhs.x,
            lhs.y - rhs.y,
            lhs.z - rhs.z);
}
const Vector3 Vector3::up       (0.0f, 0.0f, 1.0f);
const Vector3 Vector3::down     (0.0f, 0.0f, -1.0f);
const Vector3 Vector3::forward  (0.0f, 1.0f, 0.0f);
const Vector3 Vector3::back     (0.0f, -1.0f, 0.0f);
const Vector3 Vector3::right    (1.0f, 0.0f, 0.0f);
const Vector3 Vector3::left     (-1.0f, 0.0f, 0.0f);

const Vector3 Vector3::zero     (0.0f, 0.0f, 0.0f);
const Vector3 Vector3::one     (1.0f, 1.0f, 1.0f);
// --------------- Vector3 ------------------


} // namespace
