#ifndef CORE_QUATERNION_H
#define CORE_QUATERNION_H

#include "Essential.h"

namespace core {

class Quaternion {
public:
    /**
     * Default constructor, representing no rotation
     */
    Quaternion() : w(1), x(0), y(0), z(0) { }

    Quaternion(const Quaternion& rhs) = default;

    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) { }

    /**
     * Constructs Quaternion from Euler angles
     */
    Quaternion(const Vector3& euler) { this->SetFromEuler(euler); };

    /**
     * Constructs Quaternion from Axis and rotation around it
     */
    Quaternion(const Vector3& axis, const Radian& angle) { this->SetFromAxisAngle(axis, angle); };

    /**
     * Get element of the quaternion by index
     */
    inline float operator[](const size_t i) const {
        assert( i < 4 );

        return *(&w+i);
    }

    /**
     * Get element of the quaternion by index
     */
    inline float& operator[](const size_t i) {
        assert( i < 4 );

        return *(&w+i);
    }

    /**
     * Sets Quaternion values from Axis and rotation angle around it
     */
    void SetFromAxisAngle(const Vector3& axis, const Radian& angle);

    /**
     * Sets Quaternion values from Euler angles
     */
    void SetFromEuler(const Vector3& axis);

    /**
     * Converts Quaternion to Euler angles Vector3
     */
    Vector3 ToEuler() const;


    float w, x, y, z;

};

}

#endif //CORE_QUATERNION_H
