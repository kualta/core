#include <core/Components/Transform.h>
#include <core/Entity.h>

namespace core {

Transform::Transform(Entity& parent, const string& name) : Component(parent, name) {
    parent.transform = this;
}
void Transform::Update() {
    UpdateMatrix();
}
void Transform::UpdateMatrix() {
    matrix = Matrix4::identity;

    matrix = matrix * Math::ScaleMatrix(scale);
    matrix = matrix * Math::RotationAxisMatrix(position.x, position.y, position.z);
    matrix = matrix * Math::TranslationMatrix(position);
}
void Transform::SetPosition(const Vector3 &vec) {
    position = vec;
}
void Transform::SetPosition(const Vector3 &&vec) {
    position = vec;
}
void Transform::SetRotation(const Vector3 &vec) {
    rotation = vec;
}
void Transform::SetRotation(const Vector3 &&vec) {
    rotation = vec;
}
void Transform::SetScale(const Vector3 &vec) {
    scale = vec;
}
void Transform::SetScale(const Vector3 &&vec) {
    scale = vec;
}

}