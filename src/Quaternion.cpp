#include <core/Quaternion.h>
#include <core/Math.h>

namespace core {

void Quaternion::SetFromAxisAngle(const Vector3 &axis, const Radian &angle) {

    Radian halfAngle(angle * 0.5);
    const float rSin = Math::Sin(halfAngle);

    w = Math::Cos(halfAngle);
    x = rSin * axis.x;
    y = rSin * axis.y;
    z = rSin * axis.z;
}
void Quaternion::SetFromEuler(const Vector3 &axis) {

    float xs = Math::Sin(axis.x * 0.5f);
    float xc = Math::Cos(axis.x * 0.5f);

    float ys = Math::Sin(axis.y * 0.5f);
    float yc = Math::Cos(axis.y * 0.5f);

    float zs = Math::Sin(axis.z * 0.5f);
    float zc = Math::Cos(axis.z * 0.5f);

    w = xc * yc * zc + xs * ys * zs;
    x = xs * yc * zc - xc * ys * zs;
    y = xc * ys * zc + xs * yc * zs;
    z = xc * yc * zs - xs * ys * zc;
}
Vector3 Quaternion::ToEuler() const {
    Vector3 euler;

    // roll (x-axis rotation)
    float sinx_cosy = 2 * (w * x + y * z);
    float cosx_cosy = 1 - 2 * (x * x + y * y);
    euler.x = Math::Atan2(sinx_cosy, cosx_cosy);

    // pitch (y-axis rotation)
    float siny = 2 * (w * y - z * x);
    // use 90 degrees if out of range
    euler.y = Math::Abs(siny) >= 1 ? std::copysign(M_PI / 2, siny) : Math::ASin(siny);

    // yaw (z-axis rotation)
    float sinz_cosy = 2 * (w * z + x * y);
    float cosz_cosy = 1 - 2 * (y * y + z * z);
    euler.z = Math::Atan2(sinz_cosy, cosz_cosy);

    return euler;
}

}