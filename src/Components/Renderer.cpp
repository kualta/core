#include <core/Components/Renderer.h>
#include <core/Essential.h>
#include <core/Entity.h>

#include <utility>

namespace core {

Renderer::Renderer(Entity& parent, Shader* shaderPtr, Geometry* geometryPtr, uint16_t viewId, const string& name)
: Component(parent, name), viewId(viewId), shader(shaderPtr), geometry(geometryPtr) {
    parent.assertRequiredComponent<Transform>(this);
    parent.renderer = this;
}
void Renderer::Draw() {
    bgfx::setVertexBuffer(viewId, geometry->vertexBufferHandle);
    bgfx::setIndexBuffer(geometry->indexBufferHandle);
    bgfx::setTransform(&entity->transform->matrix);

    bgfx::submit(viewId, shader->program);
}

}