#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <core/Essentials.h>
#include <core/IComponent.h>
#include <core/Entity.h>
#include <core/Math.h>
#include <core/Layer.h>

namespace core {

class Camera : public IComponent {
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

    void Tick() override;
    void Draw();

    Matrix4& GetPerspectiveMatrix();
    Matrix4& GetProjectionMatrix();

    void SetFOV(Deg fov);
    void SetNearPlane(float distance);
    void SetFarPlane(float distance);
    void SetViewport(Vector2i viewport);

    void LinkLayer(const string& name);
    void UnlinkLayer(const string& name);

protected:

    void SetProjectionMatrix(Matrix4&& projMtx);
    void SetProjectionMatrix(Matrix4& projMtx);

    void UpdatePerspectiveMatrix();
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

    Matrix4         perspectiveMtx;
    Matrix4         projectionMtx;
    vector<Layer*>  linkedLayers;
};

}

#endif //CORE_CAMERA_H
