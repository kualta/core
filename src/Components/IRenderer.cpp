#include <core/Components/IRenderer.h>
#include <core/Model.h>

namespace core {

// TODO: Add asserts to parent
IRenderer::IRenderer(Entity& parent,
                     Shader* shaderPtr,
                     const string &name)
: IComponent(parent, name),
shader(shaderPtr)
{

}
IRenderer::IRenderer(Entity &parent, Model* modelPtr, const string &name)
: IComponent(parent, name),
shader(modelPtr->shader)
{

}
void IRenderer::Tick() {
    Draw();
}

}