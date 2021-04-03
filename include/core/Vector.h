#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H

#include "Essential.h"

namespace core {

template<int dims, typename T> class Vector {
public:
    Vector() {}
    Vector(float x, float y) : x(x), y(y) {}
    Vector(int x, int y) : x(float(x)), y(float(y)) {}

    float x;
    float y;

    float* Ptr() { return &x; }
    const float* Ptr() const { return &x; }
};

template<> class Vector<2, float> {
public:
    Vector() {}
    Vector(float x, float y) : x(x), y(y) {}
    Vector(int x, int y) : x(float(x)), y(float(y)) {}

    float x;
    float y;

    Vector* Ptr() { return this; }
    const float* Ptr() const { return &x; }

};

template <> struct Vector<2, int> {
    Vector() {}
    Vector(int x, int y) : x(x), y(y) {}
    Vector(float x, float y) : x(int(x)), y(int(y)) {}

    int x;
    int y;

    int* Ptr() { return &x; }
    const int* Ptr() const { return &x; }
};

//template <> struct Vector<3, float> {
//
//};
//
//template <> struct Vector<3, int> {
//
//};

}

#endif //CORE_VECTOR_H
