#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essentials.h>
#include <core/IComponent.h>
#include <core/Math.h>
#include <core/Event.h>

namespace core {

class Transform : public IComponent {
public:
    explicit Transform(Entity& parent, const string& name = "Transform");

    Event<Matrix4> OnTransformChange;

    Matrix4& GetTransformMatrix();

    /**
     * Vector representing GetPosition of the entity
     */
    Vector3 position { 0, 0, 0 };

    /**
     * Vector representing rotation of the entity along x, y and z axis
     */
    Math::Vector3<Rad> rotation { 0.0_radf, 0.0_radf, 0.0_radf };

    /**
     * Vector representing scale of the entity by x, y and z axis
     */
    Vector3 scale { 1, 1, 1 };

protected:

    void Tick() override;

    void UpdateTransformMatrix();


    Matrix4 transformMtx;

};


}

#endif //CORE_COMPONENT_TRANSFORM_H
