#include <core/Components/Transform.h>

namespace core {

void Transform::Update() {
    UpdateMatrix();
}
void Transform::UpdateMatrix() {
//    matrix = Matrix4::identity;

    // TO BE REMOVED
    matrix *= Math::TranslationMatrix(Vector3(position.x * 1.1f, position.y * 1.1f, position.z * 1.1f));
//    matrix *= Math::ScaleMatrix(scale);
//    matrix *= Math::RotationMatrixXYZ(rotatiton.x, rotatiton.y, rotatiton.z);
//    matrix *= Math::TranslationMatrix(position);
}

Transform::Transform(Entity &parent) : Component(parent) {

}

}