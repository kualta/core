#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essentials.h>
#include <core/IComponent.h>
#include <core/Math.h>

namespace core {

class Transform : public IComponent {
public:
    explicit Transform(Entity& parent, const string& name = "Transform");

    void Tick() override;

    /**
     * Vector representing position of the entity
     */
    Vector3 position { 0, 0, 0 };

    /**
     * Vector representing rotation of the entity along x, y and z axis
     */
    Vector3 rotation { 1, 0, 0 };

    /**
     * Vector representing scale of the entity by x, y and z axis
     */
    Vector3 scale { 1, 1, 1 };
};


}

#endif //CORE_COMPONENT_TRANSFORM_H
