#include <core/Components/Camera.h>
#include <core/Color.h>
#include <core/Math.h>
#include <core/Scene.h>

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
//    parent.translate(Vector3::zAxis(5.0f));
//    parent.GetComponent<Transform>()->position = Vector3(1.0f, 1.0f, 1.0f);

    setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend);
    setViewport(GL::defaultFramebuffer.viewport().size());

//    setProjectionMatrix(Matrix4::perspectiveProjection(Deg(fov), aspectRatio, nearPlane, farPlane));
    setProjectionMatrix(Matrix4::perspectiveProjection(35.0_degf, 1.0f, 0.01f, 1000.0f));
}
void Camera::Tick() {
    Draw();
}
void Camera::Draw() {
    // TODO: Add drawing by layers
    // NOTE: Temporary solution
    for (auto renderer : Renderer::instances) {
        renderer->Draw(*this);
    }
}

}