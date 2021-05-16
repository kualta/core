#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H

#include "Essential.h"
#include "Math.h"

namespace core {

template<int dims, typename T> class Vector {

};
template<> class Vector<2, float> {
public:
    Vector() { }
    Vector(float x, float y) : x(x), y(y) { }

    float x;
    float y;
};
template<> class Vector<2, int> {
public:
    Vector() { }
    Vector(int x, int y) : x(x), y(y) { }

    int x;
    int y;
};
template<> struct Vector<3, float> {
public:
    Vector() { }
    Vector(float x, float y, float z) : x(x), y(y), z(z) { }

    float Length() const;

    float x;
    float y;
    float z;

    static const Vector3 up;
    static const Vector3 down;
    static const Vector3 forward;
    static const Vector3 back;
    static const Vector3 right;
    static const Vector3 left;

    static const Vector3 zero;
    static const Vector3 one;
};
Vector3 operator*(const Vector3 &vec, const float &num);
Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

template<> struct Vector<3, int> {
public:
    Vector() { }
    Vector(int x, int y, int z) : x(x), y(y), z(z) {}

    int x;
    int y;
    int z;
};
template<> struct Vector<4, float> {
public:
    Vector() { }
    Vector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    float x;
    float y;
    float z;
    float w;
};

}

#endif //CORE_VECTOR_H
