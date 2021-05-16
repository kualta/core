#include <core/Components/Camera.h>

namespace core {


Camera::Camera(Entity &parent) : Component(parent) {

}
void core::Camera::Update() {
    entity->transform->matrix;

    view = Math::LookAtMatrix(entity->transform->position,
                              entity->transform->rotation);

    proj = Math::ProjectionMatrix(60.0f, float(600)/ float(400), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(0, view.data, proj.data);
}


}