#include <core/Components/Camera.h>
#include <core/Color.h>

namespace core {

Camera::Camera(
        Entity& parent,
        float fovY,
        float width,
        float height,
        float nearPlane,
        float farPlane,
        const string& name)
: IComponent(parent, name),
  fov(fovY),
  aspectRatio(width/height),
  width(width),
  height(height),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
}
void Camera::Tick() {
    viewMatrix = Math::LookAtMatrix(entity->transform->position, lookAt, Vector3(0, 1, 0));
    projectionMatrix = Math::ProjectionMatrix(60.0f, float(600) / float(400), 0.1f, 100.0f, true);

    bgfx::setViewTransform(0, viewMatrix.data, projectionMatrix.data);
}
void Camera::LookAt(Vector3& point) {
    lookAt = point;
}
void Camera::LookAt(Vector3 &&point) {
    lookAt = point;
}
Matrix4 Camera::GetViewMtx() {
    return viewMatrix;
}
Matrix4 Camera::GetProjMtx() {
    return projectionMatrix;
}

}