#include <core/Components/Camera.h>
#include <core/Color.h>
#include <core/Math.h>
#include <core/Scene.h>

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
  SceneGraph::Camera3D(parent),
  fov(fovY),
  width(width),
  height(height),
  aspectRatio(width/height),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
    parent.translate(Vector3::zAxis(5.0f));

    setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend);
    setProjectionMatrix(Matrix4::perspectiveProjection(35.0_degf, 1.0f, 0.01f, 1000.0f));
    setViewport(GL::defaultFramebuffer.viewport().size());
}
void Camera::Tick() {
    draw(Scene::drawables);
}

}