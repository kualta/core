#include <core/Components/Camera.h>
#include <core/Color.h>

namespace core {

Camera::Camera(Entity* parent, float fovY, float width, float height, float near, float far, bool hmgDepth,
               const string& name)
: Component(parent, name), fov(fovY), aspectRatio(width/height), width(width), height(height),
  nearPlane(near), farPlane(far), homogeneousDepth(hmgDepth) {

    this->Start();
}
void Camera::Update() {
    viewMatrix = Math::LookAtMatrix(entity->transform->position, lookAt,Vector3(0, 1, 0));

    projectionMatrix = Math::ProjectionMatrix(60.0f, float(600) / float(400), 0.1f, 100.0f, homogeneousDepth);

    bgfx::setViewTransform(0, viewMatrix.data, projectionMatrix.data);
}
void Camera::LookAt(Vector3& point) {
    lookAt = point;
}
void Camera::LookAt(Vector3 &&point) {
    lookAt = point;
}
void Camera::Start() {
    bgfx::reset(width, height, BGFX_RESET_VSYNC);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, RgbaColor::corePurple, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width, height);
    bgfx::frame();
}


}