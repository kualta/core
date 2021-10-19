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

    Event<Matrix4>    OnTransformChange;
    Event<Vector3>    OnPositionChange;
    Event<Vector3>    OnScaleChange;
    Event<Quaternion> OnRotationChange;
    
    Matrix4&    GetTransformMatrix();
    Vector3&    GetPosition();
    Quaternion& GetRotation();
    Vector3&    GetScale();

    void SetRotation(const Quaternion& rotation);
    void SetRotation(const Quaternion&& rotation);
    void SetPosition(Vector3& position);
    void SetPosition(Vector3&& position);
    void SetScale(Vector3& scale);
    void SetScale(Vector3&& scale);

    void Translate(Vector3& translation);
    void Translate(Vector3&& translation);
    void Rotate(Quaternion& rotation);
    void Rotate(Quaternion&& rotation);
    void Scale(Vector3& scale);
    void Scale(Vector3&& scale);

protected:

    void Tick() override;
    void UpdateTransformMatrix();

    /** Vector representing position of the entity */
    Vector3    position { 0, 0, 0 };

    /** Vector representing rotation of the entity along x, y and z axis */
    Quaternion rotation { };
    
    /** Vector representing scale of the entity by x, y and z axis */
    Vector3    scale    { 1, 1, 1 };

    Matrix4 transformMtx;

};

} // namespace core

#endif //CORE_COMPONENT_TRANSFORM_H
