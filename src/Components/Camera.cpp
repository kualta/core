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