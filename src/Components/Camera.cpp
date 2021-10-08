#include <core/Components/Camera.h>
#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>
#include <core/Scene/SceneView.h>
#include <core/Scene/Scene.h>
#include <core/Color.h>
#include <core/Math.h>

namespace core {

Camera::Camera(
        Entity& parent,
        float fov,
        float width,
        float height,
        float farPlane,
        float nearPlane,
        const string& name)
: IComponent(parent, name),
  SceneGraph::Camera3D(parent),
  fov(fov),
  width(width),
  height(height),
  aspectRatio(width/height),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();

    setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend);
    setViewport(GL::defaultFramebuffer.viewport().size());
}
void Camera::Tick() {
    setProjectionMatrix(Matrix4::perspectiveProjection(Deg(fov), aspectRatio, nearPlane, farPlane) * Matrix4::translation(transform->position));
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

}