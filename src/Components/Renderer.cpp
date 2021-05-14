#include <core/Components/Renderer.h>

#include <utility>

namespace core {

void Renderer::Draw() {
    bgfx::setTransform(&entity->transform->matrix);
    bgfx::submit(viewId, shader->program);
}

Renderer::Renderer(Entity& parent, uint16_t viewId, std::vector<float>* vertices, Shader* shader)
: Component(parent), viewId(viewId), vertices(vertices), shader(shader) {
    if (!this->entity->HasComponent<Transform>()) {
        Logger::Log(WARN, OBJECT) << "Entity \"" << entity->GetInfo()
                                            << " does not have Transform component attached,"
                                            << " but has Renderer! Draw calls will result in error";
    }
}

}