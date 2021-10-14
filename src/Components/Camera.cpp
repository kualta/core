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
  fov(fov),
  aspectRatio(aspectRatio),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
    UpdatePerspectiveMatrix();
    LinkLayer("Default");
}
Camera::Camera(Entity& parent,
               Vector2 viewport,
               Deg     fov,
               float   farPlane,
               float   nearPlane)
: IComponent(parent, "Camera"),
  fov(fov),
  aspectRatio(viewport.aspectRatio()),
  nearPlane(nearPlane),
  farPlane(farPlane)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
    UpdatePerspectiveMatrix();
    LinkLayer("Default");
}
void Camera::Tick() {
    SetProjectionMatrix(perspectiveMtx * Matrix4::translation(transform->position));
    SetViewport(SceneView::GetFrameBuffer().viewport().size());
    Draw();
}
void Camera::Draw() {

    SceneView::BindBuffer();

    for (Layer* layer : linkedLayers) {
        layer->Draw(*this);
    }

    SceneView::BindColor();

    GL::defaultFramebuffer.bind();
}
void Camera::SetViewport(Vector2i vp) {
    if (vp.x() == 0 || vp.y() == 0) {
        Logger::Log(INTERNAL, ERR_HERE) << "Viewport dimentions " << vp.x() << 'x' << vp.y() << " are invalid";
//        throw std::logic_error("Viewport dimentions are invalid");
        return;
    }
    viewport = vp;
    aspectRatio = (float)viewport.x() / (float)viewport.y();
}
void Camera::SetFOV(Deg FOV) {
    fov = FOV;
    UpdatePerspectiveMatrix();
}
void Camera::SetNearPlane(float distance) {
    nearPlane = distance;
    UpdatePerspectiveMatrix();
}
void Camera::SetFarPlane(float distance) {
    farPlane = distance;
    UpdatePerspectiveMatrix();
}
void Camera::UpdatePerspectiveMatrix() {
    perspectiveMtx = Matrix4::perspectiveProjection(fov, aspectRatio, nearPlane, farPlane);
}
Matrix4& Camera::GetPerspectiveMatrix() {
    return perspectiveMtx;
}
Matrix4& Camera::GetProjectionMatrix() {
    return projectionMtx;
}
void Camera::SetProjectionMatrix(Matrix4&& projMtx) {
    projectionMtx = projMtx;
    FixAspectRatio();
}
void Camera::SetProjectionMatrix(Matrix4& projMtx) {
    projectionMtx = projMtx;
    FixAspectRatio();
}
void Camera::FixAspectRatio() {
    const Vector2& projectionScale = { Math::abs(projectionMtx[0].x()), Math::abs(projectionMtx[1].y()) };
    const Vector2& relativeAspectRatio = Vector2(viewport) * projectionScale;
    if ( projectionScale.x() == 0 || projectionScale.y() == 0 ) { return; }

    /* Extend on larger side = scale larger side down,
       Clip on smaller side = scale smaller side up  */
    Matrix4 scale = Matrix4::scaling( Vector3::pad(
            (relativeAspectRatio.x() < relativeAspectRatio.y())                   ?
            Vector2(relativeAspectRatio.y() / relativeAspectRatio.x(), 1.0f)      :
            Vector2(1.0f, relativeAspectRatio.x() / relativeAspectRatio.y()), 1.0f) );

    projectionMtx = scale * projectionMtx;
}
void Camera::LinkLayer(const string &name) {
    linkedLayers.push_back(Layer::Get(name));
}
void Camera::UnlinkLayer(const string &name) {
    linkedLayers.erase(std::remove_if(linkedLayers.begin(), linkedLayers.end(), [&](Layer* l) { return l->GetName() == name; }), linkedLayers.end());
}

}