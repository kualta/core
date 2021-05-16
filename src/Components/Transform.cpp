#include <core/Components/Transform.h>

namespace core {

void Transform::Update() {
    UpdateMatrix();
}
void Transform::UpdateMatrix() {
    matrix = Matrix4::identity;

    matrix *= Math::TranslationMatrix(Vector3(position.x * 1.1f, position.y * 1.1f, position.z * 1.1f));
    matrix *= Math::ScaleMatrix(scale);
    matrix *= Math::TranslationMatrix(position);
}

Transform::Transform(Entity &parent) : Component(parent) {

}
void Transform::SetPosition(const Vector3 &vec) {
    position = vec;
    UpdateMatrix();
}
void Transform::SetPosition(const Vector3 &&vec) {
    position = vec;
    UpdateMatrix();
}
void Transform::SetRotation(const Vector3 &vec) {
    rotation = vec;
    UpdateMatrix();
}
void Transform::SetRotation(const Vector3 &&vec) {
    rotation = vec;
    UpdateMatrix();
}
void Transform::SetScale(const Vector3 &vec) {
    scale = vec;
    UpdateMatrix();
}
void Transform::SetScale(const Vector3 &&vec) {
    scale = vec;
    UpdateMatrix();
}

}