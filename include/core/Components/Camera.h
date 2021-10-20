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
#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "core/Essentials.h"
#include "core/IComponent.h"
#include "core/LayerLinked.h"
#include "core/CameraList.h"
#include "core/Entity.h"
#include "core/Layer.h"
#include "core/Math.h"
#include "core/View.h"

namespace core {

class Camera : public IComponent, public LayerLinked<Camera> {
public:
    explicit Camera(Entity &parent,
                    float   aspectRatio = 16.0f / 9.0f,
                    Deg     fov         = 90.0_degf,
                    float   farPlane    = 100.0f,
                    float   nearPlane   = 0.1f);

    explicit Camera(Entity &parent,
                    Vector2 viewport,   // no default to avoid ambiguous call when constructed with all default params.
                    Deg     fov         = 90.0_degf,
                    float   farPlane    = 100.0f,
                    float   nearPlane   = 0.1f);

    virtual ~Camera();

    void Draw();

    Matrix4& GetPerspectiveMatrix();
    Matrix4& GetProjectionMatrix();

    void SetFOV(Deg fov);
    void SetNearPlane(float distance);
    void SetFarPlane(float distance);
    void SetViewport(Vector2i viewport);
    void SetView(View& view);
    void BindAttachedView();
    void BlitAttachedView();

protected:

    void Tick() override;
    void Start() override;

    void SetTransformMatrix(Matrix4& mtx);
    void UpdatePerspectiveMatrix();
    void UpdateProjectionMatrix();
    void UpdateLayersProjectionMatrix();
    void FixAspectRatio();

    /** Field of View */
    Deg fov;

    /** Camera viewport dimentions */
    Vector2i viewport;

    /** Camera boundaries aspect ratio */
    float aspectRatio;

    /** Near clipping plane distance */
    float nearPlane;

    /**  Far clipping plane distance */
    float farPlane;

    /** Sister transform */
    Transform* transform;

    /** Attached View camera draws onto */
    View* attachedView;

    Matrix4* transformMtx;
    Matrix4  perspectiveMtx;
    Matrix4  projectionMtx;
};

class SceneCamera : public Camera {
public:
    explicit SceneCamera(Entity &parent,
                    float   aspectRatio = 16.0f / 9.0f,
                    Deg     fov         = 90.0_degf,
                    float   farPlane    = 100.0f,
                    float   nearPlane   = 0.1f);

    explicit SceneCamera(Entity &parent,
                    Vector2 viewport,   // no default to avoid ambiguous call when constructed with all default params.
                    Deg     fov         = 90.0_degf,
                    float   farPlane    = 100.0f,
                    float   nearPlane   = 0.1f);

};


} // namespace core

#endif //CORE_CAMERA_H
