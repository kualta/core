/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essentials.h>
#include <core/IComponent.h>
#include <core/Math.h>
#include <core/Event.h>

namespace core {

class Transform : public IComponent {
public:
    explicit Transform(Entity& entity, const string& name = "Transform");

    Event<Matrix4>    OnTransformChange;
    Event<Vector3>    OnPositionChange;
    Event<Vector3>    OnScaleChange;
    Event<Quaternion> OnRotationChange;
    
    Matrix4&    GetWorldTransformMatrix();
    Matrix4&    GetTransformMatrix();
    Vector3&    GetPosition();
    Quaternion& GetRotation();
    Vector3&    GetScale();

    void SetParent(Transform* parent);
    void SetRotation(const Quaternion& rotation);
    void SetRotation(const Quaternion&& rotation);
    void SetPosition(Vector3& position);
    void SetPosition(Vector3&& position);
    void SetScale(Vector3& scale);
    void SetScale(Vector3&& scale);

    void Translate(Vector3& translation);
    void Translate(Vector3&& translation);
    void Rotate(Quaternion& rotation);
    void Rotate(Quaternion&& rotation);
    void Scale(Vector3& scale);
    void Scale(Vector3&& scale);

protected:

    void Tick() override;
    void UpdateTransform();

    /** Vector representing position of the entity */
    Vector3    position { 0, 0, 0 };

    /** Vector representing rotation of the entity along x, y and z axis */
    Quaternion rotation { };
    
    /** Vector representing scale of the entity by x, y and z axis */
    Vector3    scale    { 1, 1, 1 };

    Matrix4     localTransform { };
    Matrix4*    parentTransform;

};

} // namespace core

#endif //CORE_COMPONENT_TRANSFORM_H
