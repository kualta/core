#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "Color.h"

#include <Magnum/Math/Vector.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Vector4.h>
#include <Magnum/Math/BoolVector.h>
#include "Magnum/Math/Matrix.h"
#include "Magnum/Math/Matrix3.h"
#include "Magnum/Math/Matrix4.h"
#include "Magnum/Math/RectangularMatrix.h"
#include "Magnum/Math/Bezier.h"
#include "Magnum/Math/Angle.h"
#include "Magnum/Math/Range.h"

using namespace Magnum;
using namespace Math::Literals;
namespace core {

typedef Math::Half Half;
typedef Math::Rad<float> Rad;
typedef Math::Deg<float> Deg;

typedef Math::BoolVector<2> BoolVector2;
typedef Math::BoolVector<3> BoolVector3;
typedef Math::BoolVector<4> BoolVector4;
typedef Math::Vector2<Float> Vector2;
typedef Math::Vector3<Float> Vector3;
typedef Math::Vector4<Float> Vector4;
typedef Math::Vector2<UnsignedByte> Vector2ub;
typedef Math::Vector3<UnsignedByte> Vector3ub;
typedef Math::Vector4<UnsignedByte> Vector4ub;
typedef Math::Vector2<Byte> Vector2b;
typedef Math::Vector3<Byte> Vector3b;
typedef Math::Vector4<Byte> Vector4b;
typedef Math::Vector2<UnsignedShort> Vector2us;
typedef Math::Vector3<UnsignedShort> Vector3us;
typedef Math::Vector4<UnsignedShort> Vector4us;
typedef Math::Vector2<Short> Vector2s;
typedef Math::Vector3<Short> Vector3s;
typedef Math::Vector4<Short> Vector4s;
typedef Math::Vector2<UnsignedInt> Vector2ui;
typedef Math::Vector3<UnsignedInt> Vector3ui;
typedef Math::Vector4<UnsignedInt> Vector4ui;
typedef Math::Vector2<Int> Vector2i;
typedef Math::Vector3<Int> Vector3i;
typedef Math::Vector4<Int> Vector4i;
typedef Math::Vector2<Rad> RadVector2;
typedef Math::Vector3<Rad> RadVector3;
typedef Math::Vector4<Rad> RadVector4;
typedef Math::Vector2<Deg> DegVector2;
typedef Math::Vector3<Deg> DegVector3;
typedef Math::Vector4<Deg> DegVector4;
typedef Math::Matrix3<Float> Matrix3;
typedef Math::Matrix4<Float> Matrix4;
typedef Math::Matrix2x2<Float> Matrix2x2;
typedef Math::Matrix3x3<Float> Matrix3x3;
typedef Math::Matrix4x4<Float> Matrix4x4;
typedef Math::Matrix2x3<Float> Matrix2x3;
typedef Math::Matrix3x2<Float> Matrix3x2;
typedef Math::Matrix2x4<Float> Matrix2x4;
typedef Math::Matrix4x2<Float> Matrix4x2;
typedef Math::Matrix3x4<Float> Matrix3x4;
typedef Math::Matrix4x3<Float> Matrix4x3;
typedef Math::Matrix2x2<Byte> Matrix2x2b;
typedef Math::Matrix2x3<Byte> Matrix2x3b;
typedef Math::Matrix2x4<Byte> Matrix2x4b;
typedef Math::Matrix3x2<Byte> Matrix3x2b;
typedef Math::Matrix3x3<Byte> Matrix3x3b;
typedef Math::Matrix3x4<Byte> Matrix3x4b;
typedef Math::Matrix4x2<Byte> Matrix4x2b;
typedef Math::Matrix4x3<Byte> Matrix4x3b;
typedef Math::Matrix4x4<Byte> Matrix4x4b;
typedef Math::Matrix2x2<Short> Matrix2x2s;
typedef Math::Matrix2x3<Short> Matrix2x3s;
typedef Math::Matrix2x4<Short> Matrix2x4s;
typedef Math::Matrix3x2<Short> Matrix3x2s;
typedef Math::Matrix3x3<Short> Matrix3x3s;
typedef Math::Matrix3x4<Short> Matrix3x4s;
typedef Math::Matrix4x2<Short> Matrix4x2s;
typedef Math::Matrix4x3<Short> Matrix4x3s;
typedef Math::Matrix4x4<Short> Matrix4x4s;
typedef Math::QuadraticBezier2D<Float> QuadraticBezier2D;
typedef Math::QuadraticBezier3D<Float> QuadraticBezier3D;
typedef Math::CubicBezier2D<Float> CubicBezier2D;
typedef Math::CubicBezier3D<Float> CubicBezier3D;
typedef Math::CubicHermite1D<Float> CubicHermite1D;
typedef Math::CubicHermite2D<Float> CubicHermite2D;
typedef Math::CubicHermite3D<Float> CubicHermite3D;
typedef Math::CubicHermiteComplex<Float> CubicHermiteComplex;
typedef Math::CubicHermiteQuaternion<Float> CubicHermiteQuaternion;
typedef Math::Complex<Float> Complex;
typedef Math::DualComplex<Float> DualComplex;
typedef Math::Quaternion<Float> Quaternion;
typedef Math::DualQuaternion<Float> DualQuaternion;
typedef Math::Constants<Float> Constants;
typedef Math::Range1D<Float> Range1D;
typedef Math::Range2D<Float> Range2D;
typedef Math::Range3D<Float> Range3D;
typedef Math::Range1D<Int> Range1Di;
typedef Math::Range2D<Int> Range2Di;
typedef Math::Range3D<Int> Range3Di;
typedef Math::Frustum<Float> Frustum;
typedef Math::Vector2<Half> Vector2h;
typedef Math::Vector3<Half> Vector3h;
typedef Math::Vector4<Half> Vector4h;
typedef Math::Matrix2x2<Half> Matrix2x2h;
typedef Math::Matrix2x3<Half> Matrix2x3h;
typedef Math::Matrix2x4<Half> Matrix2x4h;
typedef Math::Matrix3x2<Half> Matrix3x2h;
typedef Math::Matrix3x3<Half> Matrix3x3h;
typedef Math::Matrix3x4<Half> Matrix3x4h;
typedef Math::Matrix4x2<Half> Matrix4x2h;
typedef Math::Matrix4x3<Half> Matrix4x3h;
typedef Math::Matrix4x4<Half> Matrix4x4h;
typedef Math::Vector2<Double> Vector2d;
typedef Math::Vector3<Double> Vector3d;
typedef Math::Vector4<Double> Vector4d;
typedef Math::Matrix3<Double> Matrix3d;
typedef Math::Matrix4<Double> Matrix4d;
typedef Math::Matrix2x2<Double> Matrix2x2d;
typedef Math::Matrix3x3<Double> Matrix3x3d;
typedef Math::Matrix4x4<Double> Matrix4x4d;
typedef Math::Matrix2x3<Double> Matrix2x3d;
typedef Math::Matrix3x2<Double> Matrix3x2d;
typedef Math::Matrix2x4<Double> Matrix2x4d;
typedef Math::Matrix4x2<Double> Matrix4x2d;
typedef Math::Matrix3x4<Double> Matrix3x4d;
typedef Math::Matrix4x3<Double> Matrix4x3d;
typedef Math::QuadraticBezier2D<Float> QuadraticBezier2Dd;
typedef Math::QuadraticBezier3D<Float> QuadraticBezier3Dd;
typedef Math::CubicBezier2D<Float> CubicBezier2Dd;
typedef Math::CubicBezier3D<Float> CubicBezier3Dd;
typedef Math::CubicHermite1D<Double> CubicHermite1Dd;
typedef Math::CubicHermite2D<Double> CubicHermite2Dd;
typedef Math::CubicHermite3D<Double> CubicHermite3Dd;
typedef Math::CubicHermiteComplex<Double> CubicHermiteComplexd;
typedef Math::CubicHermiteQuaternion<Double> CubicHermiteQuaterniond;
typedef Math::Complex<Double> Complexd;
typedef Math::DualComplex<Double> DualComplexd;
typedef Math::Quaternion<Double> Quaterniond;
typedef Math::DualQuaternion<Double> DualQuaterniond;
typedef Math::Constants<Double> Constantsd;
typedef Math::Deg<Double> Degd;
typedef Math::Rad<Double> Radd;
typedef Math::Range1D<Double> Range1Dd;
typedef Math::Range2D<Double> Range2Dd;
typedef Math::Range3D<Double> Range3Dd;
typedef Math::Frustum<Double> Frustumd;

} // namespace

#endif //CORE_MATH_H
