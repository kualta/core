#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essential.h>
#include <core/IComponent.h>
#include <core/Math.h>

namespace core {

class Transform : public IComponent {
public:
    explicit Transform(Entity& parent, const string& name = "Transform");

    void Tick() override;

    /**
     * Transform matrix that describes current position, rotation and scale of entity in world space
     */
    Matrix4 matrix { Matrix4::identity };

    /**
     * Vector representing position of the entity
     */
    Vector3 position { 0, 0, 0 };

    /**
     * Vector representing rotation of the entity along x, y and z axis
     */
    Vector3 rotation { 0, 0, 0 };

    /**
     * Vector representing scale of the entity by x, y and z axis
     */
    Vector3 scale { 1, 1, 1 };

protected:

    void UpdateMatrix();

private:

};


}

#endif //CORE_COMPONENT_TRANSFORM_H
