#include <core/Components/BgfxRenderer.h>
#include <core/Essential.h>
#include <core/Entity.h>

#include <utility>

namespace core {

BgfxRenderer::BgfxRenderer(Entity& parent,
                           Shader* shaderPtr,
                           BgfxMesh* bgfxMesh,
                           uint16_t viewId,
                           const string& name)
: IRenderer(parent, shaderPtr, name),
mesh(bgfxMesh),
viewId(viewId)
{
    parent.assertRequiredComponent<Transform>(this);
    parent.renderer = this;
}
BgfxRenderer::BgfxRenderer(Entity& parent,
                           Model* modelPtr,
                           uint16_t viewId,
                           const string& name)
: IRenderer(parent, modelPtr, name),
viewId(viewId)
{
    parent.assertRequiredComponent<Transform>(this);
    parent.renderer = this;
}
void BgfxRenderer::Draw() {
    bgfx::setVertexBuffer(viewId, mesh->vertexBufferHandle);
    bgfx::setIndexBuffer(mesh->indexBufferHandle);
    bgfx::setTransform(&entity->transform->matrix);

    bgfx::submit(viewId, shader->program);
}

}