#include <core/Components/Transform.h>

namespace core {

void Transform::Update() {
    UpdateTransform();
}
void Transform::UpdateTransform() {
    transform *= Math::TranslationMatrix(position);
    transform *= Math::RotationMatrixXYZ(rotatiton);
    transform *= Math::ScaleMatrix(scale);
}


}