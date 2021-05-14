#include <core/Components/Transform.h>

namespace core {

void Transform::Update() {
    UpdateMatrix();
}
void Transform::UpdateMatrix() {
    matrix = Matrix4::identity;

    matrix *= Math::ScaleMatrix(scale);
    matrix *= Math::RotationMatrixXYZ(rotatiton.x, rotatiton.y, rotatiton.z);
    matrix *= Math::TranslationMatrix(position);
}

Transform::Transform(Entity &parent) : Component(parent) {

}

}