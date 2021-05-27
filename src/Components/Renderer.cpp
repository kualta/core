#include <core/Components/Renderer.h>
#include <core/Essential.h>
#include <core/Entity.h>

#include <utility>

namespace core {

Renderer::Renderer(Entity& parent, Shader* shaderPtr, Mesh* geometryPtr, uint16_t viewId, const string& name) :
Component(parent, name),
viewId(viewId),
shader(shaderPtr),
mesh(geometryPtr)
{
    parent.assertRequiredComponent<Transform>(this);
    parent.renderer = this;
}
Renderer::Renderer(Entity &parent, Model *model, uint16_t viewId, const string &name) :
Component(parent, name),
viewId(viewId),
shader(model->shader),
mesh(model->mesh)
{
    parent.assertRequiredComponent<Transform>(this);
    parent.renderer = this;
}
void Renderer::Tick() {
    Draw();
}
void Renderer::Draw() {
    bgfx::setVertexBuffer(viewId, mesh->vertexBufferHandle);
    bgfx::setIndexBuffer(mesh->indexBufferHandle);
    bgfx::setTransform(&entity->transform->matrix);

    bgfx::submit(viewId, shader->program);
}

}