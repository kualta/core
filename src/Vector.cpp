#include <core/Vector.h>

namespace core {

// --------------- Vector3 ------------------
Vector3 Vector<3, float>::Normalize() {
    const float invLen = 1.0f / Length();
    return *this * invLen;
}

float Vector<3, float>::Length() {
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
// --------------- Vector3 ------------------


} // namespace
