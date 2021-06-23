#include <core/Components/VkRenderer.h>

namespace core {

VkRenderer::VkRenderer(Entity& parent,
                       Model* modelPtr,
                       const string& name)
: IRenderer(parent, modelPtr, name)
{

}
VkRenderer::~VkRenderer() {

}
void VkRenderer::Draw() {

}

}