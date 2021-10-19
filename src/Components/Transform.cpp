#include <core/Components/Transform.h>
#include <core/Entity.h>

namespace core {

Transform::Transform(Entity& parent, const string& name) : IComponent(parent, name) {
    parent.assertExistingComponent<Transform>();
}
void Transform::Tick() {

}
void Transform::UpdateTransformMatrix() {
    transformMtx = Matrix4::from(rotation.toMatrix(), position)
                 * Matrix4::scaling(scale);
    
    OnTransformChange.Trigger(transformMtx);
}
Matrix4& Transform::GetTransformMatrix() {
    return transformMtx;
}
Vector3& Transform::GetPosition() {
    return position;
};
Quaternion& Transform::GetRotation() {
    return rotation;
}
Vector3& Transform::GetScale() {
    return scale;
}
void Transform::SetPosition(Vector3& vec) {
    position = vec;
    UpdateTransformMatrix();
    OnPositionChange.Trigger(position);
}
void Transform::SetPosition(Vector3&& vec) {
    position = vec;
    UpdateTransformMatrix();
    OnPositionChange.Trigger(position);
}
void Transform::SetRotation(const Quaternion& rot) {
    rotation = rot;
    UpdateTransformMatrix();
    OnRotationChange.Trigger(rotation);
}
void Transform::SetRotation(const Quaternion&& rot) {
    rotation = rot;
    UpdateTransformMatrix();
    OnRotationChange.Trigger(rotation);
}
void Transform::SetScale(Vector3& vec) {
    scale = vec;
    UpdateTransformMatrix();
    OnScaleChange.Trigger(scale);
}
void Transform::SetScale(Vector3&& vec) {
    scale = vec;
    UpdateTransformMatrix();
    OnScaleChange.Trigger(scale);
}
void Transform::Translate(Vector3& vec) {
    SetPosition(position + vec);
}
void Transform::Translate(Vector3&& vec) {
    SetPosition(position + vec);
}
void Transform::Rotate(Quaternion& rot) {
    SetRotation(rotation * rot);
}
void Transform::Rotate(Quaternion&& rot) {
    SetRotation(rotation * rot);
}
void Transform::Scale(Vector3& vec) {
    SetScale(scale + vec);
}
void Transform::Scale(Vector3&& vec) {
    SetScale(scale + vec);
}

}