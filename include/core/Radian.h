#ifndef CORE_RADIAN_H
#define CORE_RADIAN_H


namespace core {

class Radian {
public:
    float data;

    explicit Radian ( float r=0 ) : data(r) {}
    Radian (const Radian& other) : data(other.GetValue()) {}

    float GetValue() const { return data; }
    float ToDegrees() const { return data * 180.0f / 3.14159265359f; };

    Radian& operator = ( const float& f ) { data = f; return *this; }
    Radian& operator = ( const Radian& r ) = default;
    Radian operator + ( const Radian& r ) const { return Radian (data + r.data ); }
    Radian& operator += ( const Radian& r ) { data += r.data; return *this; }
    Radian operator - () const { return Radian(-data); }
    Radian operator - ( const Radian& r ) const { return Radian (data - r.data ); }
    Radian& operator -= ( const Radian& r ) { data -= r.data; return *this; }
    Radian operator * ( float f ) const { return Radian (data * f ); }
    Radian operator * ( const Radian& f ) const { return Radian (data * f.data ); }
    Radian& operator *= ( float f ) { data *= f; return *this; }
    Radian operator / ( float f ) const { return Radian (data / f ); }
    Radian& operator /= ( float f ) { data /= f; return *this; }

    bool operator <  ( const Radian& r ) const { return data < r.data; }
    bool operator <= ( const Radian& r ) const { return data <= r.data; }
    bool operator == ( const Radian& r ) const { return data == r.data; }
    bool operator != ( const Radian& r ) const { return data != r.data; }
    bool operator >= ( const Radian& r ) const { return data >= r.data; }
    bool operator >  ( const Radian& r ) const { return data > r.data; }

    inline friend std::ostream& operator <<
            ( std::ostream& o, const Radian& v )
    {
        o << "Radian(" << v.GetValue() << ")";
        return o;
    }

}; // class Radian

}

#endif //CORE_RADIAN_H
