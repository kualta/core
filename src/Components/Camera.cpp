#include <core/Components/Camera.h>
#include <core/Color.h>
#include <core/Math.h>
#include <core/Scene.h>

namespace core {

SceneGraph::Camera3D* Camera::camera;

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
    cameraObject
        .setParent(&Scene::scene)
        .translate(Vector3::zAxis(5.0f));

    (*(camera = new SceneGraph::Camera3D { cameraObject } ))
        .setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Matrix4::perspectiveProjection(35.0_degf, 1.0f, 0.01f, 1000.0f))
        .setViewport(GL::defaultFramebuffer.viewport().size());
}
void Camera::Tick() {
    camera->draw(Scene::drawables);
}

}