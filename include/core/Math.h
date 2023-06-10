/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
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
#include "Magnum/Math/Quaternion.h"

using namespace Math::Literals;
namespace core {

typedef Magnum::Math::Half Half;
typedef Magnum::Math::Rad<float> Rad;
typedef Magnum::Math::Deg<float> Deg;
typedef Magnum::Math::BoolVector<2> BoolVector2;
typedef Magnum::Math::BoolVector<3> BoolVector3;
typedef Magnum::Math::BoolVector<4> BoolVector4;
typedef Magnum::Math::Vector2<Float> Vector2;
typedef Magnum::Math::Vector3<Float> Vector3;
typedef Magnum::Math::Vector4<Float> Vector4;
typedef Magnum::Math::Vector2<UnsignedByte> Vector2ub;
typedef Magnum::Math::Vector3<UnsignedByte> Vector3ub;
typedef Magnum::Math::Vector4<UnsignedByte> Vector4ub;
typedef Magnum::Math::Vector2<Byte> Vector2b;
typedef Magnum::Math::Vector3<Byte> Vector3b;
typedef Magnum::Math::Vector4<Byte> Vector4b;
typedef Magnum::Math::Vector2<UnsignedShort> Vector2us;
typedef Magnum::Math::Vector3<UnsignedShort> Vector3us;
typedef Magnum::Math::Vector4<UnsignedShort> Vector4us;
typedef Magnum::Math::Vector2<Short> Vector2s;
typedef Magnum::Math::Vector3<Short> Vector3s;
typedef Magnum::Math::Vector4<Short> Vector4s;
typedef Magnum::Math::Vector2<UnsignedInt> Vector2ui;
typedef Magnum::Math::Vector3<UnsignedInt> Vector3ui;
typedef Magnum::Math::Vector4<UnsignedInt> Vector4ui;
typedef Magnum::Math::Vector2<Int> Vector2i;
typedef Magnum::Math::Vector3<Int> Vector3i;
typedef Magnum::Math::Vector4<Int> Vector4i;
typedef Magnum::Math::Vector2<Rad> RadVector2;
typedef Magnum::Math::Vector3<Rad> RadVector3;
typedef Magnum::Math::Vector4<Rad> RadVector4;
typedef Magnum::Math::Vector2<Deg> DegVector2;
typedef Magnum::Math::Vector3<Deg> DegVector3;
typedef Magnum::Math::Vector4<Deg> DegVector4;
typedef Magnum::Math::Matrix3<Float> Matrix3;
typedef Magnum::Math::Matrix4<Float> Matrix4;
typedef Magnum::Math::Matrix2x2<Float> Matrix2x2;
typedef Magnum::Math::Matrix3x3<Float> Matrix3x3;
typedef Magnum::Math::Matrix4x4<Float> Matrix4x4;
typedef Magnum::Math::Matrix2x3<Float> Matrix2x3;
typedef Magnum::Math::Matrix3x2<Float> Matrix3x2;
typedef Magnum::Math::Matrix2x4<Float> Matrix2x4;
typedef Magnum::Math::Matrix4x2<Float> Matrix4x2;
typedef Magnum::Math::Matrix3x4<Float> Matrix3x4;
typedef Magnum::Math::Matrix4x3<Float> Matrix4x3;
typedef Magnum::Math::Matrix2x2<Byte> Matrix2x2b;
typedef Magnum::Math::Matrix2x3<Byte> Matrix2x3b;
typedef Magnum::Math::Matrix2x4<Byte> Matrix2x4b;
typedef Magnum::Math::Matrix3x2<Byte> Matrix3x2b;
typedef Magnum::Math::Matrix3x3<Byte> Matrix3x3b;
typedef Magnum::Math::Matrix3x4<Byte> Matrix3x4b;
typedef Magnum::Math::Matrix4x2<Byte> Matrix4x2b;
typedef Magnum::Math::Matrix4x3<Byte> Matrix4x3b;
typedef Magnum::Math::Matrix4x4<Byte> Matrix4x4b;
typedef Magnum::Math::Matrix2x2<Short> Matrix2x2s;
typedef Magnum::Math::Matrix2x3<Short> Matrix2x3s;
typedef Magnum::Math::Matrix2x4<Short> Matrix2x4s;
typedef Magnum::Math::Matrix3x2<Short> Matrix3x2s;
typedef Magnum::Math::Matrix3x3<Short> Matrix3x3s;
typedef Magnum::Math::Matrix3x4<Short> Matrix3x4s;
typedef Magnum::Math::Matrix4x2<Short> Matrix4x2s;
typedef Magnum::Math::Matrix4x3<Short> Matrix4x3s;
typedef Magnum::Math::Matrix4x4<Short> Matrix4x4s;
typedef Magnum::Math::QuadraticBezier2D<Float> QuadraticBezier2D;
typedef Magnum::Math::QuadraticBezier3D<Float> QuadraticBezier3D;
typedef Magnum::Math::CubicBezier2D<Float> CubicBezier2D;
typedef Magnum::Math::CubicBezier3D<Float> CubicBezier3D;
typedef Magnum::Math::CubicHermite1D<Float> CubicHermite1D;
typedef Magnum::Math::CubicHermite2D<Float> CubicHermite2D;
typedef Magnum::Math::CubicHermite3D<Float> CubicHermite3D;
typedef Magnum::Math::CubicHermiteComplex<Float> CubicHermiteComplex;
typedef Magnum::Math::CubicHermiteQuaternion<Float> CubicHermiteQuaternion;
typedef Magnum::Math::Complex<Float> Complex;
typedef Magnum::Math::DualComplex<Float> DualComplex;
typedef Magnum::Math::Quaternion<Float> Quaternion;
typedef Magnum::Math::DualQuaternion<Float> DualQuaternion;
typedef Magnum::Math::Constants<Float> Constants;
typedef Magnum::Math::Range1D<Float> Range1D;
typedef Magnum::Math::Range2D<Float> Range2D;
typedef Magnum::Math::Range3D<Float> Range3D;
typedef Magnum::Math::Range1D<Int> Range1Di;
typedef Magnum::Math::Range2D<Int> Range2Di;
typedef Magnum::Math::Range3D<Int> Range3Di;
typedef Magnum::Math::Frustum<Float> Frustum;
typedef Magnum::Math::Vector2<Half> Vector2h;
typedef Magnum::Math::Vector3<Half> Vector3h;
typedef Magnum::Math::Vector4<Half> Vector4h;
typedef Magnum::Math::Matrix2x2<Half> Matrix2x2h;
typedef Magnum::Math::Matrix2x3<Half> Matrix2x3h;
typedef Magnum::Math::Matrix2x4<Half> Matrix2x4h;
typedef Magnum::Math::Matrix3x2<Half> Matrix3x2h;
typedef Magnum::Math::Matrix3x3<Half> Matrix3x3h;
typedef Magnum::Math::Matrix3x4<Half> Matrix3x4h;
typedef Magnum::Math::Matrix4x2<Half> Matrix4x2h;
typedef Magnum::Math::Matrix4x3<Half> Matrix4x3h;
typedef Magnum::Math::Matrix4x4<Half> Matrix4x4h;
typedef Magnum::Math::Vector2<Double> Vector2d;
typedef Magnum::Math::Vector3<Double> Vector3d;
typedef Magnum::Math::Vector4<Double> Vector4d;
typedef Magnum::Math::Matrix3<Double> Matrix3d;
typedef Magnum::Math::Matrix4<Double> Matrix4d;
typedef Magnum::Math::Matrix2x2<Double> Matrix2x2d;
typedef Magnum::Math::Matrix3x3<Double> Matrix3x3d;
typedef Magnum::Math::Matrix4x4<Double> Matrix4x4d;
typedef Magnum::Math::Matrix2x3<Double> Matrix2x3d;
typedef Magnum::Math::Matrix3x2<Double> Matrix3x2d;
typedef Magnum::Math::Matrix2x4<Double> Matrix2x4d;
typedef Magnum::Math::Matrix4x2<Double> Matrix4x2d;
typedef Magnum::Math::Matrix3x4<Double> Matrix3x4d;
typedef Magnum::Math::Matrix4x3<Double> Matrix4x3d;
typedef Magnum::Math::QuadraticBezier2D<Float> QuadraticBezier2Dd;
typedef Magnum::Math::QuadraticBezier3D<Float> QuadraticBezier3Dd;
typedef Magnum::Math::CubicBezier2D<Float> CubicBezier2Dd;
typedef Magnum::Math::CubicBezier3D<Float> CubicBezier3Dd;
typedef Magnum::Math::CubicHermite1D<Double> CubicHermite1Dd;
typedef Magnum::Math::CubicHermite2D<Double> CubicHermite2Dd;
typedef Magnum::Math::CubicHermite3D<Double> CubicHermite3Dd;
typedef Magnum::Math::CubicHermiteComplex<Double> CubicHermiteComplexd;
typedef Magnum::Math::CubicHermiteQuaternion<Double> CubicHermiteQuaterniond;
typedef Magnum::Math::Complex<Double> Complexd;
typedef Magnum::Math::DualComplex<Double> DualComplexd;
typedef Magnum::Math::Quaternion<Double> Quaterniond;
typedef Magnum::Math::DualQuaternion<Double> DualQuaterniond;
typedef Magnum::Math::Constants<Double> Constantsd;
typedef Magnum::Math::Deg<Double> Degd;
typedef Magnum::Math::Rad<Double> Radd;
typedef Magnum::Math::Range1D<Double> Range1Dd;
typedef Magnum::Math::Range2D<Double> Range2Dd;
typedef Magnum::Math::Range3D<Double> Range3Dd;
typedef Magnum::Math::Frustum<Double> Frustumd;


namespace Math {

constexpr static Matrix4 identityMatrix { };

using Magnum::Math::max;
using Magnum::Math::min;
using Magnum::Math::minmax;
using Magnum::Math::exp;
using Magnum::Math::cos;
using Magnum::Math::sin;
using Magnum::Math::asin;
using Magnum::Math::acos;
using Magnum::Math::tan;
using Magnum::Math::atan;
using Magnum::Math::ceil;
using Magnum::Math::floor;
using Magnum::Math::lerp;
using Magnum::Math::slerp;
using Magnum::Math::pow;
using Magnum::Math::sqrt;
using Magnum::Math::abs;
using Magnum::Math::log;
using Magnum::Math::log2;

} // namespace Math

} // namespace core


#endif //CORE_MATH_H
