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

/**
 * Handles perspective projection and Layer::Draw() calls
 */
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

    /**
     * Calls Layer::Draw() on every linked layer
     * @details Everything on the layer gets drawn onto the attached view
     */
    void Draw();

    /**
     * Get internal perspective matrix of the camera
     * @return Matrix4&
     */
    Matrix4& GetPerspectiveMatrix();
    
    /**
     * Get internal projection matrix of the camera
     * @return Matrix4&
     */
    Matrix4& GetProjectionMatrix();

    /**
     * Set FOV of the camera
     * @details Updates internal perspecive matrix of the camera
     */
    void SetFOV(Deg fov);
    
    /**
     * Set distance to the near clipping plane of the camera
     * @details Updates internal perspecive matrix of the camera
     */
    void SetNearPlane(float distance);
    
    /**
     * Set distance to the further clipping plane of the camera
     * @details Updates internal perspecive matrix of the camera
     */
    void SetFarPlane(float distance);
    
    /**
     * Set viewport of the camera
     * @details Updates internal perspecive matrix of the camera
     */
    void SetViewport(Vector2i viewport);
    
    /**
     * Attach View camera will draw onto
     */
    void SetView(View& view);
    
    /**
     * Binds currently attached view's framebuffer for draw
     */
    void BindAttachedView();
    
    /**
     * Blits currently attached view's framebuffer on default one
     * @details After that, binds back default framebuffer
     */
    void BlitAttachedView();

protected:

    void Tick() override;
    void Start() override;

    /**
     * Sets internal transfrom matrix
     * @details Updates internal projection matrix of the camera
     */
    void SetTransformMatrix(Matrix4& mtx);
    
    /**
     * Recalculates perspective matrix of the camera
     */
    void UpdatePerspectiveMatrix();
    
    /**
     * Recalculates projection matrix of the camera
     */
    void UpdateProjectionMatrix();
    
    /**
     * Sets current projection matrix for use on every attached layer
     */
    void UpdateLayersProjectionMatrix();
    
    /**
     * Modifies projection matrix to match desired aspect ratio
     */
    void FixAspectRatio();
    

    /** Field of View */
    Deg fov;

    /** Camera viewport dimentions */
    Vector2i viewport;

    /** Camera boundaries aspect ratio */
    float aspectRatio;

    /** Near clipping plane distance */
    float nearPlane;

    /** Far clipping plane distance */
    float farPlane;

    /** Sibling transform */
    Transform* transform;

    /** Attached View camera draws on */
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
