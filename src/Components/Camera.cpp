#include <core/Components/Camera.h>

namespace core {


Camera::Camera(Entity &parent) : Component(parent) {

}
void core::Camera::Update() {
    entity->transform->matrix;

    Vector4 view;
    Vector4 proj;
    const bx::Vec3 at = {0.0f, 0.0f,  0.0f};
    const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
    bx::mtxLookAt(view, eye, at);
    bx::mtxProj(proj, 60.0f, float(600) / float(400), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
    bgfx::setViewTransform(0, view, proj);
}


}