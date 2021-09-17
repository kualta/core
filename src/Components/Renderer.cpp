#include <core/Components/Renderer.h>
#include <core/Components/Transform.h>
#include <core/Components/Camera.h>
#include <core/Model.h>

namespace core {

Renderer::Renderer(Entity& parent, Model* model, const string& name)
: IComponent(parent, name),
  model(model)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
}
void Renderer::Tick() {

}
void Renderer::Draw(Camera& camera) {
    Matrix4 transformMtx = Matrix4::translation(transform->position)
                         * Matrix4::rotationX(Rad(transform->rotation.x()))
                         * Matrix4::rotationY(Rad(transform->rotation.y()))
                         * Matrix4::rotationZ(Rad(transform->rotation.z()))
                         * Matrix4::scaling(transform->scale);

    model->Draw(transformMtx, camera);
}

}