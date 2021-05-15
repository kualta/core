#include <core/Components/Renderer.h>
#include <core/Entity.h>

#include <utility>

namespace core {

Renderer::Renderer(Entity& parent, Shader* shaderPtr, Geometry* geometryPtr, uint16_t viewId)
: Component(parent), viewId(viewId), shader(shaderPtr), geometry(geometryPtr) {

}
void Renderer::Draw() {
    bgfx::setVertexBuffer(0, geometry->vbh);
    bgfx::setIndexBuffer(geometry->ibh);
    bgfx::setTransform(&entity->transform->matrix.data);

    bgfx::submit(viewId, shader->program);
}

}