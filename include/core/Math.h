#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "Essential.h"
#include "Vector.h"
#include "Matrix.h"
#include <ostream>

namespace core {


class Math {
public:

    static inline float DegreesToRadians(float degrees) { return degrees * PI / float(180.0); }
    static inline float RadiansToDegrees(float radians) { return radians * float(180.0) / PI; }

    /**
     * Calculates dot product of two Vectors
     * @details dot product = first.x * second.x
     *                      + first.y * second.y
     *                      + first.z * second.z;
     * @param lhs - first Vector
     * @param rhs - second Vector
     * @return dot product between lhs and rhs
     */
    static inline float Dot(const Vector3& lhs, const Vector3& rhs);

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
    static inline Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

    /**
     * Generates new translation matrix to vector
     * @param pos - position translate to
     * @return Matrix4 translation matrix
     */
    static Matrix4 TranslationMatrix(const Vector3 &pos);

    /**
     * Generates new rotation matrix around X, Y and Z axis
     * @param rotX - Rotation around X axis
     * @param rotY - Rotation around Y axis
     * @param rotZ - Rotation around Z axis
     * @return Matrix4 rotation matrix
     */
    static Matrix4 RotationMatrixXYZ(float rotX, float rotY, float rotZ);

    /**
     * Generates new scale matrix
     * @param x - scale by X axis
     * @param y - scale by Y axis
     * @param z - scale by Z axis
     * @return Matrix4 scale matrix
     */
    static Matrix4 ScaleMatrix(Vector3 scale);

    static const float PI;
    static const float TWO_PI;
    static const float TAU;
    static const float HALF_PI;
    static const float LOG2;

    static float Sqrt(float num);
}; // class Math


class Degree {
    float value;

public:
    explicit Degree ( float d=0 ) : value(d) {}
    Degree (const Degree& d) : value(d.GetValue()) {}

    float GetValue() const { return value; };
    float ToRadians() const { return Math::DegreesToRadians(value); };

    Degree& operator = ( const float& f ) { value = f; return *this; }
    Degree& operator = ( const Degree& d ) = default;
    Degree operator + ( const Degree& d ) const { return Degree (value + d.value ); }
    Degree& operator += ( const Degree& d ) { value += d.value; return *this; }
    Degree operator - () const { return Degree(-value); }
    Degree operator - ( const Degree& d ) const { return Degree (value - d.value ); }
    Degree& operator -= ( const Degree& d ) { value -= d.value; return *this; }
    Degree operator * ( float f ) const { return Degree (value * f ); }
    Degree operator * ( const Degree& f ) const { return Degree (value * f.value ); }
    Degree& operator *= ( float f ) { value *= f; return *this; }
    Degree operator / ( float f ) const { return Degree (value / f ); }
    Degree& operator /= ( float f ) { value /= f; return *this; }

    bool operator <  ( const Degree& d ) const { return value <  d.value; }
    bool operator <= ( const Degree& d ) const { return value <= d.value; }
    bool operator == ( const Degree& d ) const { return value == d.value; }
    bool operator != ( const Degree& d ) const { return value != d.value; }
    bool operator >= ( const Degree& d ) const { return value >= d.value; }
    bool operator >  ( const Degree& d ) const { return value >  d.value; }

    inline friend std::ostream& operator <<
        ( std::ostream& o, const Degree& v )
    {
        o << "Degree(" << v.GetValue() << ")";
        return o;
    }
}; // class Degree

class Radian {
    float value;

public:
    explicit Radian ( float r=0 ) : value(r) {}
    Radian (const Radian& other) : value(other.GetValue()) {}

    float GetValue() const { return value; }
    float ToDegrees() const { return Math::RadiansToDegrees(value); };

    Radian& operator = ( const float& f ) { value = f; return *this; }
    Radian& operator = ( const Radian& r ) = default;
    Radian operator + ( const Radian& r ) const { return Radian (value + r.value ); }
    Radian& operator += ( const Radian& r ) { value += r.value; return *this; }
    Radian operator - () const { return Radian(-value); }
    Radian operator - ( const Radian& r ) const { return Radian (value - r.value ); }
    Radian& operator -= ( const Radian& r ) { value -= r.value; return *this; }
    Radian operator * ( float f ) const { return Radian (value * f ); }
    Radian operator * ( const Radian& f ) const { return Radian (value * f.value ); }
    Radian& operator *= ( float f ) { value *= f; return *this; }
    Radian operator / ( float f ) const { return Radian (value / f ); }
    Radian& operator /= ( float f ) { value /= f; return *this; }

    bool operator <  ( const Radian& r ) const { return value <  r.value; }
    bool operator <= ( const Radian& r ) const { return value <= r.value; }
    bool operator == ( const Radian& r ) const { return value == r.value; }
    bool operator != ( const Radian& r ) const { return value != r.value; }
    bool operator >= ( const Radian& r ) const { return value >= r.value; }
    bool operator >  ( const Radian& r ) const { return value >  r.value; }

    inline friend std::ostream& operator <<
        ( std::ostream& o, const Radian& v )
    {
        o << "Radian(" << v.GetValue() << ")";
        return o;
    }
}; // class Radian


} // namespace

#endif //CORE_MATH_H
