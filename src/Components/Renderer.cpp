#include <core/Components/Renderer.h>
#include <core/Entity.h>

#include <utility>

namespace core {

Renderer::Renderer(Entity& parent, uint16_t viewId, float* buf, Shader* shader)
: Component(parent), viewId(viewId), verticesBuf(buf), shader(shader) {
    if (!this->entity->HasComponent<Transform>()) {
        Logger::Log(WARN, OBJECT) << "Entity \"" << entity->GetInfo()
                                            << " does not have Transform component attached,"
                                            << " but has Renderer! Draw calls will result in error";
    }
}
void Renderer::Draw() {
    bgfx::setTransform(&entity->transform->matrix);
    bgfx::submit(viewId, shader->program);
}

}