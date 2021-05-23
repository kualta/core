#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "Vector.h"
#include "Essential.h"
#include "Matrix.h"
#include "Radian.h"
#include "Degree.h"
#include <ostream>

namespace core {


class Math {
public:

    static inline Radian DegreesToRadians(const Degree& degrees) { return Radian(degrees.data * PI / float(180.0)); }
    static inline Radian DegreesToRadians(const Degree&& degrees) { return Radian(degrees.data * PI / float(180.0)); }

    static inline Degree RadiansToDegrees(const Radian& radians) { return Degree(radians.data * float(180.0) / PI); }
    static inline Degree RadiansToDegrees(const Radian&& radians) { return Degree(radians.data * float(180.0) / PI); }

    /**
     * Calculates dot product of two Vectors
     * @details dot product = first.x * second.x
     *                      + first.y * second.y
     *                      + first.z * second.z;
     * @param lhs - first Vector
     * @param rhs - second Vector
     * @return dot product between lhs and rhs
     */
    static inline float Dot(const Vector3& lhs, const Vector3& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    };

    /**
     * Calculates cross product between two vectors
     * @details cross product = (
                first.y * second.z - first.z * second.y,
                first.z * second.x - first.x * second.z,
                first.x * second.y - first.y * second.x)
     * @param lhs - first Vector
     * @param rhs - second Vector
     * @return Vector3 cross product between lhs and rhs
     */
    static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

    /**
     * Calculates normalized version of vector
     * @details magnitude of normalized vector is 1
     * @param vec - lvalue ref Vector to normalize
     * @return Vector3 normalized vector
     */
    static Vector3 Normalize(const Vector3& vec);

    /**
     * Calculates normalized version of vector
     * @details magnitude of normalized vector is 1
     * @param vec - rvalue ref Vector to normalize
     * @return Vector3 normalized vector
     */
    static Vector3 Normalize(const Vector3&& vec);

    /**
     * Calculates matrix that represents transformation
     * from pos to lookAt
     * @param pos - position of transform
     * @param lookAt - point transform looks at
     * @param worldUp - world up vector (default = {0, 0, 1})
     * @return Matrix4 transform matrix
     */
    static Matrix4 LookAtMatrix(const Vector3& pos,
                                const Vector3& lookAt,
                                const Vector3& worldUp = Vector3::up);

    /**
     * Generates new translation matrix to vector
     * @param pos - position translate to
     * @return Matrix4 translation matrix
     */
    static Matrix4 TranslationMatrix(const Vector3& pos);

    /**
     * Generates new rotation matrix around X, Y and Z axis
     * @param rotX - Rotation around X axis
     * @param rotY - Rotation around Y axis
     * @param rotZ - Rotation around Z axis
     * @return Matrix4 rotation matrix
     */
    static Matrix4 EulerRotationMatrix(const Vector3& euler);

    /**
     * Generates new projection matrix in top to bottom, left to right rectangle, clipped by
     * near and far planes.
     * @param near - distance to near clipping plane
     * @param far - distance to far clipping plane
     * @param hmgNdc - is clip space homogeneous?
     * @return Matrix4 projection matrix
     */
    static Matrix4 ProjectionMatrix(float top, float bottom, float left, float right, float near, float far, bool hmgNdc);

    /**
     * Generates new projection matrix in given Y axis fov with aspect ratio, clipped by near and far planes.
     * @param fovY - Field of View by Y axis
     * @param aspect - aspect ratio
     * @param near - distance to near clipping plane
     * @param far - distance to far clipping plane
     * @param hmgNdc - is clip space homogeneous?
     * @return Matrix4 projection matrix
     */
    static Matrix4 ProjectionMatrix(float fovY, float aspect, float near, float far, bool hmgNdc);

    /**
     * Generates new projection matrix in given rectangle, clipped by near and far planes.
     * @param rect - projection Rect
     * @param near - distance to near clipping plane
     * @param far - distance to far clipping plane
     * @param hmgNdc - is clip space homogeneous?
     * @return Matrix4 projection matrix
     */
    static Matrix4 ProjectionMatrix(Rect rect, float near, float far, bool hmgNdc);

    /**
     * Generates new scale matrix
     * @param x - scale by X axis
     * @param y - scale by Y axis
     * @param z - scale by Z axis
     * @return Matrix4 scale matrix
     */
    static Matrix4 ScaleMatrix(Vector3 scale);

    /**
     * Computes absolute value of a
     */
    static inline float Abs(float a) { return std::abs(a); };

    /**
     * Calculates square root of number
     */
    static inline float Sqrt(float a) { return std::sqrt(a); };

    /**
     * Calculates sine of value in radians
     */
    static inline float Sin(const Radian& radian) { return std::sin(radian.GetValue()); };
    static inline float Sin(float a) { return std::sin(a); };

    /**
     * Calculates sine of value in radians
     */
    static inline float Cos(const Radian& radian) { return std::cos(radian.GetValue()); };
    static inline float Cos(float a) { return std::cos(a); };

    /**
     * Calculates tangent of value in radians
     */
    static inline float Tan(const Radian& radian) { return std::tan(radian.GetValue()); };
    static inline float Tan(float a) { return std::tan(a); };

    /**
     * Calculates arccos of value in radians
     */
    static inline float ACos(const Radian& radian) { return std::acos(radian.GetValue()); };
    static inline float ACos(float a) { return std::acos(a); };

    /**
     * Calculates arcsin of value in radians
     */
    static inline float ASin(const Radian& radian) { return std::asin(radian.GetValue()); };
    static inline float ASin(float a) { return std::asin(a); };

    static inline float Atan2(float a, float b) { return std::atan2(a, b); };

    static const float PI;
    static const float TWO_PI;
    static const float TAU;
    static const float HALF_PI;
    static const float LOG2;

}; // class Math

} // namespace

#endif //CORE_MATH_H
