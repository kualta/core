#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Math.h>

namespace core {

class Transform : public Component {
public:
    explicit Transform(Entity* parent = nullptr,
                       const string& name = "Transform");

    void Update() override;

    void SetPosition(const Vector3& vec);
    void SetPosition(const Vector3&& vec);

    void SetRotation(const Vector3& vec);
    void SetRotation(const Vector3&& vec);

    void SetScale(const Vector3& vec);
    void SetScale(const Vector3&& vec);

    /**
     * Transform matrix that describes current position, rotation and scale of entity in world space
     */
    Matrix4 matrix { Matrix4::identity };

    /**
     * Vector representing position of the entity in world space
     * @warning This value is read-only, do not modify this value directly,
     *          use SetPosition instead.
     * @readonly
     */
    Vector3 position { 0, 0, 0 };

    /**
     * Vector representing rotation of the entity along x, y and z axis in world space
     * @warning This value is read-only, do not modify this value directly,
     *          use SetRotation instead.
     * @readonly
     */
    Vector3 rotation {0, 0, 0 };

    /**
     * Vector representing scale of the entity in world space
     * @warning This value is read-only, do not modify this value directly,
     *          use SetRotation instead.
     * @readonly
     */
    Vector3 scale { 1, 1, 1 };

protected:

    void UpdateMatrix();

private:

};


}

#endif //CORE_COMPONENT_TRANSFORM_H
