#include <core/Components/Transform.h>

namespace core {

void Transform::Update() {
    UpdateTransform();
}
void Transform::UpdateTransform() {
    transform = Matrix4::identity;

    transform *= Math::ScaleMatrix(scale);
    transform *= Math::RotationMatrixXYZ(rotatiton.x, rotatiton.y, rotatiton.z);
    transform *= Math::TranslationMatrix(position);
}

}