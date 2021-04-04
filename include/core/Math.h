#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "Essential.h"
#include <ostream>

namespace core {


class Math {
public:

    static inline float DegreesToRadians(float degrees) { return degrees * PI / float(180.0); }
    static inline float RadiansToDegrees(float radians) { return radians * float(180.0) / PI; }
    static Matrix4 TranslationMatrix(const Vector3 &vec);

    static const float PI;
    static const float TWO_PI;
    static const float TAU;
    static const float HALF_PI;
    static const float LOG2;
}; // class Math


class Degree {
    float value;

public:
    explicit Degree ( float d=0 ) : value(d) {}
    Degree (const Degree& d) : value(d.GetValue()) {}
    Degree& operator = ( const float& f ) { value = f; return *this; }
    Degree& operator = ( const Degree& d ) = default;

    float GetValue() const { return value; };
    float ToRadians() const { return Math::DegreesToRadians(value); };

    const Degree& operator + () const { return *this; }
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
    Radian& operator = ( const float& f ) { value = f; return *this; }
    Radian& operator = ( const Radian& r ) = default;

    float GetValue() const { return value; }
    float ToDegrees() const { return Math::RadiansToDegrees(value); };

    const Radian& operator + () const { return *this; }
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
};


} // namespace

#endif //CORE_MATH_H
