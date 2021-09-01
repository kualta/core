#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <core/Essential.h>
#include <core/IComponent.h>
#include <core/Entity.h>

namespace core {

class Camera : public IComponent {
public:
    explicit Camera(Entity&     parent,
                    float         fovY = 90.0f,
                    float        width = 600.0f,
                    float       height = 400.0f,
                    float    nearPlane = 0.1f,
                    float     farPlane = 100.0f,
                    const string& name = "Camera");

    void Tick() override;

    void LookAt(Vector3& point);
    void LookAt(Vector3&& point);
    Matrix4 GetViewMtx();
    Matrix4 GetProjMtx();

protected:

    Matrix4 viewMatrix;
    Matrix4 projectionMatrix;

    /**
     * Point camera is pointing towards
     */
    Vector3 lookAt = Vector3::zero;

    /**
     * Field of View by Y axis
     */
    float fov = 90.0f;

    /**
     * Width of camera rectangle
     */
    float width = 600.0f;

    /**
     * Height of camera rectangle
     */
    float height = 400.0f;

    /**
     * Camera boundaries aspect ratio
     */
    float aspectRatio = width / height;

    /**
     * Near clipping plane distance
     */
    float nearPlane = 0.1f;

    /**
     * Far clipping plane distance
     */
    float farPlane = 100.0f;
};

}

#endif //CORE_CAMERA_H
