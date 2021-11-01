/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
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
    transformMtx = &transform->GetTransformMatrix();
    UpdatePerspectiveMatrix();
    CameraList::Get()->Register(this);
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
    transformMtx = &transform->GetTransformMatrix();
    UpdatePerspectiveMatrix();
    CameraList::Get()->Register(this);
}
Camera::~Camera() {
    CameraList::Get()->Unregister(this);
}
void Camera::Start() {
    transform->OnTransformChange.Subscribe([&](Matrix4& mtx) {
        SetTransformMatrix(mtx);
    });
}
void Camera::Tick() {

}
void Camera::Draw() {
    attachedView->Bind();
    for (const shared<Layer>& layer : linkedLayers) {
        layer->Draw();
    }
    attachedView->Blit();

    GL::defaultFramebuffer.bind();
}
void Camera::SetViewport(Vector2i v) {
    if (v.x() == 0 || v.y() == 0) {
        Logger::Log(INTERNAL, ERR_HERE) << "Viewport dimensions " << v.x() << 'x' << v.y() << " are invalid";
        return;
    }
    viewport = v;
    aspectRatio = (float)viewport.x() / (float)viewport.y();
    UpdatePerspectiveMatrix();
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
    UpdateProjectionMatrix();
}
void Camera::SetTransformMatrix(Matrix4& mtx) {
    transformMtx = &mtx;
    UpdateProjectionMatrix();
}
void Camera::UpdateProjectionMatrix() {
    projectionMtx = perspectiveMtx * (*transformMtx);
    FixAspectRatio();
    UpdateLayersProjectionMatrix();
}
Matrix4& Camera::GetPerspectiveMatrix() {
    return perspectiveMtx;
}
Matrix4& Camera::GetProjectionMatrix() {
    return projectionMtx;
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
void Camera::SetView(View& view) {
    attachedView = &view;
    attachedView->OnResize.Subscribe([&](Vector2i& vec) {
        SetViewport(vec);
    });
}
void Camera::UpdateLayersProjectionMatrix() {
    for (const shared<Layer>& layer : linkedLayers) {
        layer->SetProjectionMatrix(projectionMtx);
    }
}
void Camera::BindAttachedView() {
    attachedView->Bind();
}
void Camera::BlitAttachedView() {
    attachedView->Blit();
}
SceneCamera::SceneCamera(Entity& parent, float aspectRatio, Deg fov, float farPlane, float nearPlane)
: Camera(parent, aspectRatio, fov, farPlane, nearPlane)
{

}
SceneCamera::SceneCamera(Entity& parent, Vector2 viewport, Deg fov, float farPlane, float nearPlane)
: Camera(parent, viewport, fov, farPlane, nearPlane)
{

}

}