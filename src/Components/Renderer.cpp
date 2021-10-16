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
void Renderer::Tick() {
    // FIXME: Move draw call from Camera to Renderer::Tick()
    Matrix4 transformMtx = Matrix4::translation(transform->position)
                         * Matrix4::rotationX(transform->rotation.x())
                         * Matrix4::rotationY(transform->rotation.y())
                         * Matrix4::rotationZ(transform->rotation.z())
                         * Matrix4::scaling(transform->scale);

    SetTransformMatrix(transformMtx);
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
    model->SetLight(light);
}

}