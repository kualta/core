#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

#include "Essential.h"

namespace core {


template<int cols, int rows, typename T> class Matrix {
public:
    static Matrix3 Translate(const Vector3 &v);
    static Matrix4 Translate(const Vector4 &v);

protected:
    T mtx[cols][rows];
};

template<> class Matrix<3, 3, float> {
public:

protected:
    float mtx[3][3];
};

template<> class Matrix<4, 4, float> {
public:

protected:
    float mtx[3][3];
};



} // namespace core

#endif //CORE_MATRIX_H
