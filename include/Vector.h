#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H


namespace core {

template<int dims, typename T>
class Vector {
public:
    /// Default constructor is not initialized for efficiency
    Vector(T _x, T _y) {}
    Vector(T _x, T _y, T _z) {}
    Vector(T _x, T _y, T _z, T _w)  {}

    Vector() {}

    T* ptr() { return data; }
    const T* ptr() const { return data; }

public:
    T data[dims];
};


}

#endif //CORE_VECTOR_H
