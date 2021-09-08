#include <core/Components/Renderer.h>
#include <core/Model.h>

namespace core {

Renderer::Renderer(Entity& parent, Model* model, const string& name)
: IComponent(parent, name),
  shader(model->shader),
  mesh(model->mesh)
{

}
void Renderer::Tick() {
    Draw();
}
void Renderer::Draw() {
    shader->Draw(mesh);
}

}