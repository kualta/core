#ifndef CORE_DEGREE_H
#define CORE_DEGREE_H

#include "Essential.h"

#include <cmath>

namespace core {

class Degree {
public:
    float data;

    explicit Degree ( float d=0 ) : data(d) {}
    Degree (const Degree& d) : data(d.GetValue()) {}

    float GetValue() const { return data; };
    float ToRadians() const { return data * 180.0f / 3.14159265359f; };

    Degree& operator = ( const float& f ) { data = f; return *this; }
    Degree& operator = ( const Degree& d ) = default;
    Degree operator + ( const Degree& d ) const { return Degree (data + d.data ); }
    Degree& operator += ( const Degree& d ) { data += d.data; return *this; }
    Degree operator - () const { return Degree(-data); }
    Degree operator - ( const Degree& d ) const { return Degree (data - d.data ); }
    Degree& operator -= ( const Degree& d ) { data -= d.data; return *this; }
    Degree operator * ( float f ) const { return Degree (data * f ); }
    Degree operator * ( const Degree& f ) const { return Degree (data * f.data ); }
    Degree& operator *= ( float f ) { data *= f; return *this; }
    Degree operator / ( float f ) const { return Degree (data / f ); }
    Degree& operator /= ( float f ) { data /= f; return *this; }

    bool operator <  ( const Degree& d ) const { return data < d.data; }
    bool operator <= ( const Degree& d ) const { return data <= d.data; }
    bool operator == ( const Degree& d ) const { return data == d.data; }
    bool operator != ( const Degree& d ) const { return data != d.data; }
    bool operator >= ( const Degree& d ) const { return data >= d.data; }
    bool operator >  ( const Degree& d ) const { return data > d.data; }

    inline friend std::ostream& operator <<
            ( std::ostream& o, const Degree& v )
    {
        o << "Degree(" << v.GetValue() << ")";
        return o;
    }

}; // class Degree

}

#endif //CORE_DEGREE_H
