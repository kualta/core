#ifndef CORE_MATH_H
#define CORE_MATH_H

namespace core {


class Math {
public:

    static inline float DegreesToRadians(float degrees) { return degrees * fDeg2Rad; }
    static inline float RadiansToDegrees(float radians) { return radians * fRad2Deg; }

    static const float PI;
    static const float TWO_PI;
    static const float HALF_PI;
    static const float fDeg2Rad;
    static const float fRad2Deg;
    static const float LOG2;
};

class Degree {
    float value;

public:
    explicit Degree ( float d=0 ) : value(d) {}
    Degree ( const Radian& r ) : mDeg(r.valueDegrees()) {}
    Degree (const Ogre::Degree& rhs) : mDeg(rhs.mDeg) {}
    Degree& operator = ( const float& f ) { value = f; return *this; }
    Degree& operator = ( const Degree& d ) { value = d.value; return *this; }

    float valueRadians() const;
    float valueAngleUnits() const;

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
        o << "Degree(" << v.ToDegrees() << ")";
        return o;
    }
};



} // namespace

#endif //CORE_MATH_H
