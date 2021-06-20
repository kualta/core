#include <core/Components/IRenderer.h>
#include <core/Model.h>

namespace core {

// TODO: Add asserts to parent
IRenderer::IRenderer(Entity& parent,
                     Shader* shaderPtr,
                     BgfxMesh* meshPtr,
                     const string &name)
: IComponent(parent, name),
mesh(meshPtr),
shader(shaderPtr)
{

}
IRenderer::IRenderer(Entity &parent,
                     Model *modelPtr,
                     const string &name)
        : IComponent(parent, name),
          mesh(modelPtr->mesh),
          shader(modelPtr->shader)
{

}
void IRenderer::Tick() {
    Draw();
}

}