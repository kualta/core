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