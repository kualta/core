#include <core/Components/Camera.h>
#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>
#include <core/Scene/SceneView.h>
#include <core/Scene/Scene.h>
#include <core/Color.h>
#include <core/Math.h>

namespace core {

Camera::Camera(Entity& parent,
               float   aspectRatio,
               Deg     fov,
               float   farPlane,
               float   nearPlane)
: IComponent(parent, "Camera"),
  SceneGraph::Camera3D(parent),
  fov(fov),
  aspectRatio(aspectRatio),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();

    setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Clip);
    RecalculatePerspective();
}
Camera::Camera(Entity &parent,
               Vector2 viewport,
               Deg     fov,
               float   farPlane,
               float   nearPlane)
: IComponent(parent, "Camera"),
  SceneGraph::Camera3D(parent),
  fov(fov),
  aspectRatio(viewport.aspectRatio()),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();

    setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Clip);
    RecalculatePerspective();
}
void Camera::Tick() {
    setProjectionMatrix(perspectiveMtx * Matrix4::translation(transform->position));
    SetViewport(SceneView::GetFrameBuffer().viewport().size());
    Draw();
}
void Camera::Draw() {
    // TODO: Add drawing by layers
    // NOTE: Temporary solution

    SceneView::BindBuffer();

    for (auto renderer : Renderer::instances) {
        renderer->Draw(*this);
    }

    SceneView::BindColor();

    GL::defaultFramebuffer.bind();
}
void Camera::SetViewport(Vector2i viewport) {
    aspectRatio = (float)viewport.x() / (float)viewport.y();
    setViewport(viewport);
}
void Camera::SetFOV(Deg FOV) {
    fov = FOV;
    RecalculatePerspective();
}
void Camera::SetNearPlane(float distance) {
    nearPlane = distance;
    RecalculatePerspective();
}
void Camera::SetFarPlane(float distance) {
    farPlane = distance;
    RecalculatePerspective();
}
void Camera::RecalculatePerspective() {
    perspectiveMtx = Matrix4::perspectiveProjection(fov, aspectRatio, nearPlane, farPlane);
}
Matrix4& Camera::GetPerspectiveMatrix() {
    return perspectiveMtx;
}
Matrix4& Camera::GetProjectionMatrix() {
    projectionMtx = projectionMatrix();
    return projectionMtx;
}

}