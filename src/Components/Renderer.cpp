#include <core/Components/Renderer.h>

namespace core {

void Renderer::Draw() {
    bgfx::setTransform(&entity->transform->transform);
    bgfx::submit(viewId, shader->program);
}

}