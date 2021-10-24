/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
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
    SetScale(scale * vec);
}
void Transform::Scale(Vector3&& vec) {
    SetScale(scale * vec);
}

}