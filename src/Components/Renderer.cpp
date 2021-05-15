#include <core/Components/Renderer.h>
#include <core/Entity.h>

#include <utility>

namespace core {

Renderer::Renderer(Entity& parent, Shader* shaderPtr, uint16_t viewId, ColorVertex* verBuf, uint16_t* triBuf)
: Component(parent), viewId(viewId), verticesBuf(verBuf), trianglesBuf(triBuf), shader(shaderPtr) {
    if (!this->entity->HasComponent<Transform>()) {
        Logger::Log(WARN, OBJECT) << "Entity " << entity->GetInfo()
                                            << " does not have Transform component attached, but has Renderer!"
                                            << " Draw calls will result in error";
    }
}
void Renderer::Draw() {
    bgfx::setTransform(&entity->transform->matrix);
    bgfx::submit(viewId, shader->program);
}

}