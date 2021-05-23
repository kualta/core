#include <core/Components/Transform.h>
#include <core/Entity.h>

namespace core {

Transform::Transform(Entity& parent, const string& name) : Component(parent, name) {
    parent.assertExistingComponent<Transform>();
    parent.transform = this;
}
void Transform::Tick() {
    UpdateMatrix();
}
void Transform::UpdateMatrix() {
    matrix = Matrix4::identity;

    matrix = matrix * Math::ScaleMatrix(scale);
    matrix = matrix * Math::EulerRotationMatrix(rotation);
    matrix = matrix * Math::TranslationMatrix(position);
}

}