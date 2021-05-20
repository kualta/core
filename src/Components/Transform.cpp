#include <core/Components/Transform.h>

namespace core {

Transform::Transform(Entity *parent, const string& name) : Component(parent, name) {

}
void Transform::Update() {
    UpdateMatrix();
}
void Transform::UpdateMatrix() {
    matrix = Matrix4::identity;

    matrix *= Math::TranslationMatrix(position);
    matrix *= Math::ScaleMatrix(scale);
    matrix *= Math::RotationAxisMatrix(rotation.x, rotation.y, rotation.z);
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