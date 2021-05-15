#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Math.h>

namespace core {

class Transform : public Component {
public:
    Transform(Entity& parent);

    void Update() override;

    /**
     * Transform matrix that describes current position, rotation and scale of entity
     */
    Matrix4 matrix { Matrix4::identity };

protected:

    void UpdateMatrix();

private:

    Vector3 position { 0, 0, 0 };
    Vector3 rotatiton { 0, 0, 0 };
    Vector3 scale { 1, 1, 1 };
};


}

#endif //CORE_COMPONENT_TRANSFORM_H
