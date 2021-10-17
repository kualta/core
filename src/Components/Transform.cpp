#include <core/Components/Transform.h>
#include <core/Entity.h>

namespace core {

Transform::Transform(Entity& parent, const string& name) : IComponent(parent, name) {
    parent.assertExistingComponent<Transform>();
}
void Transform::Tick() {
    UpdateTransformMatrix();
}
void Transform::UpdateTransformMatrix() {
    transformMtx = Matrix4::translation(position)
                 * Matrix4::rotationX(rotation.x())
                 * Matrix4::rotationY(rotation.y())
                 * Matrix4::rotationZ(rotation.z())
                 * Matrix4::scaling(scale);
    OnTransformChange.Trigger(transformMtx);
}
Matrix4& Transform::GetTransformMatrix() {
    return transformMtx;
}

}