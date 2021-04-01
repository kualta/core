#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H

#include <cassert>


namespace core {

template<int dims, typename T>
class Vector {
public:
    /// Default constructor is not initialized for efficiency
    Vector() {}
    Vector(T x, T y)
    {
        static_assert(dims > 1, "must have at least 2 dims");
        vec[0] = x;
        vec[1] = y;
    }
    Vector(T x, T y, T z)
    {
        static_assert(dims > 2, "must have at least 3 dims");
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }
    Vector(T x, T y, T z, T w)
    {
        static_assert(dims > 3, "must have at least 4 dims");
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
        vec[3] = w;
    }

    T* Get() { return vec; }
    const T* Get() const { return vec; }


    T operator[](size_t i) const
    {
        assert(i < dims);
        return Get()[i];
    }

    T& operator[](size_t i)
    {
        assert(i < dims);
        return Get()[i];
    }

    bool operator==(const Vector& v) const
    {
        for (int i = 0; i < dims; i++)
            if (Get()[i] != v[i])
                return false;
        return true;
    }

    bool operator!=(const Vector& v) const { return !(*this == v); }

    /** Returns true if the vector's scalar components are all greater
        that the ones of the vector it is compared against.
    */
    bool operator<(const Vector& rhs) const
    {
        for (int i = 0; i < dims; i++)
            if (!(Get()[i] < rhs[i]))
                return false;
        return true;
    }

    /** Returns true if the vector's scalar components are all smaller
        that the ones of the vector it is compared against.
    */
    bool operator>(const Vector& rhs) const
    {
        for (int i = 0; i < dims; i++)
            if (!(Get()[i] > rhs[i]))
                return false;
        return true;
    }

    /// Get dot product of this vector with other.
    T DotProduct(const Vector<dims, T>& other) const
    {
        T ret = 0;
        for (int i = 0; i < dims; i++)
            ret += Get()[i] * other.Get()[i];
        return ret;
    }

public:
    T vec[dims];
};


}

#endif //CORE_VECTOR_H
