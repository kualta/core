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

    matrix *= Math::TranslationMatrix(Vector3(position.x * 1.1f, position.y * 1.1f, position.z * 1.1f));
    matrix *= Math::ScaleMatrix(scale);
    matrix *= Math::TranslationMatrix(position);
}

Transform::Transform(Entity &parent) : Component(parent) {

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