#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

#include "Essential.h"
#include <ostream>

namespace core {

template<int rows, int cols, typename T> class Matrix {
public:
    static Matrix3 Translate(const Vector3 &vec);
    static Matrix4 Translate(const Vector4 &vec);

protected:
    T mtx[rows][cols];
};

template<> class Matrix<3, 3, float> {
public:
    Matrix(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22 )
    {
        mtx[0][0] = m00; mtx[0][1] = m01; mtx[0][2] = m02;
        mtx[1][0] = m10; mtx[1][1] = m11; mtx[1][2] = m12;
        mtx[2][0] = m20; mtx[2][1] = m21; mtx[2][2] = m22;
    }

    const float* operator[] (int row) const {
        return mtx[row];
    }
    float* operator[] (int row) {
        return mtx[row];
    }

protected:
    float mtx[3][3];

    static const Matrix3 zero;
    static const Matrix3 identity;
};

template<> class Matrix<4, 4, float> {
public:
    Matrix() {}
    Matrix(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33 )
    {
        mtx[0][0] = m00; mtx[0][1] = m01; mtx[0][2] = m02; mtx[0][3] = m03;
        mtx[1][0] = m10; mtx[1][1] = m11; mtx[1][2] = m12; mtx[1][3] = m13;
        mtx[2][0] = m20; mtx[2][1] = m21; mtx[2][2] = m22; mtx[2][3] = m23;
        mtx[3][0] = m30; mtx[3][1] = m31; mtx[3][2] = m32; mtx[3][3] = m33;
    }
    Matrix(float m) {
        mtx[0][0] = m; mtx[0][1] = m; mtx[0][2] = m; mtx[0][3] = m;
        mtx[1][0] = m; mtx[1][1] = m; mtx[1][2] = m; mtx[1][3] = m;
        mtx[2][0] = m; mtx[2][1] = m; mtx[2][2] = m; mtx[2][3] = m;
        mtx[3][0] = m; mtx[3][1] = m; mtx[3][2] = m; mtx[3][3] = m;
    }


    const float* operator[] (int row) const {
        return mtx[row];
    }
    float* operator[] (int row) {
        return mtx[row];
    }

    float* GetPtr() {
        return &mtx[0][0];
    }


    static const Matrix4 zero;
    static const Matrix4 identity;
protected:
    float mtx[4][4];
};

Matrix4 operator*(const Matrix4 &lhs, const Matrix4 &rhs);

inline std::ostream& operator<<(std::ostream& o, const Matrix4 &mat)
{
    o << "Matrix4x4(" << std::endl;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            o << mat[i][j];
            if(j != 3)
                o << ", ";
        }

        if(i != 3)
            o << std::endl;
    }
    o << ")";
    return o;
}

} // namespace core

#endif //CORE_MATRIX_H
