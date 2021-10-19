#include <core/Components/Renderer.h>
#include <core/Components/Transform.h>
#include <core/Components/Camera.h>
#include <core/Model.h>

namespace core {

Renderer::Renderer(Entity& parent, const shared<Model>& model, const string& name)
: IComponent(parent, name),
  model(model)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
}
void Renderer::Start() {
    transform->OnTransformChange.Subscribe([&](Matrix4& mtx) { SetTransformMatrix(mtx); });
}
void Renderer::Tick() {

}
void Renderer::Draw() {
    model->Draw();
}
void Renderer::SetProjectionMatrix(Matrix4& mtx) {
    model->SetProjectionMatrix(mtx);
}
void Renderer::SetTransformMatrix(Matrix4& mtx) {
    model->SetTransformMatrix(mtx);
    model->SetNormalMatrix(mtx);
}
void Renderer::SetLight(Light& light) {
    switch (light.GetLightType()) {
        case Point:         model->SetPointLight(light);        break;
        case Directional:   model->SetDirectionalLight(light);  break;
        case Spot: throw std::logic_error("Not yet implemented"); break;
        case Area: throw std::logic_error("Not yet implemented"); break;
    }
}

}