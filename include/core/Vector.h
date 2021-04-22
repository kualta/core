#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H

#include "Essential.h"

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
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;
};
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
