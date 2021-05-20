#include <core/Components/Renderer.h>
#include <core/Essential.h>
#include <core/Entity.h>

#include <utility>

namespace core {

Renderer::Renderer(
        Entity& parent,
        Shader& shader,
        Geometry& geometry,
        uint16_t viewId,
        const string& name)
:   Component(parent, name),
    viewId(viewId),
    shader(shader),
    geometry(geometry)
{
    parent.assertRequiredComponent<Transform>(this);
    parent.renderer = this;
}
void Renderer::Draw() {
    bgfx::setVertexBuffer(viewId, geometry.vertexBufferHandle);
    bgfx::setIndexBuffer(geometry.indexBufferHandle);
    bgfx::setTransform(&parent->transform->matrix);

    bgfx::submit(viewId, shader.program);
    static int counter = 0;
    Logger::Log(INFO) << ++counter;
}
void Renderer::Update() {

}

}