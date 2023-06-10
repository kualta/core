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
#include <core/Components/Light.h>
#include <core/Entity.h>
#include <core/Components/Transform.h>

namespace core {

Light::Light(Entity& parent, LightType lightType, Color3 color, float range, const string& name)
: IComponent(parent, name), color(color), specularColor(color), range(range), lightType(lightType)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
}
void Light::Tick() {
    for (auto layer : linkedLayers) {
        layer->SetLight(*this);
    }
}
void Light::SetColor(Color3& c) {
    color = c;
}
void Light::SetColor(Color3&& c) {
    color = c;
}
void Light::SetSpecularColor(Color3& c) {
    specularColor = c;
}
void Light::SetSpecularColor(Color3&& c) {
    specularColor = c;
}
void Light::SetRange(float r) {
    range = r;
}
Color3 &Light::GetColor() {
    return color;
}
Color3 &Light::GetSpecularColor() {
    return specularColor;
}
float Light::GetRange() {
    return range;
}
LightType Light::GetLightType() const {
    return lightType;
}
void Light::SetLightType(LightType type) {
    lightType = type;
}
Vector3& Light::GetPosition() {
    return transform->GetPosition();
}
Vector3 Light::GetDirection() {
    return transform->GetRotation().toMatrix()[2];
}

}