#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <core/Essential.h>
#include <core/Component.h>

#include <core/Entity.h>
#include <bx/math.h>

namespace core {

class Camera : public Component {
public:
    Camera(Entity* parent = nullptr,
           float fovY = 90.0f,
           float width = 600.0f,
           float height = 400.0f,
           float near = 0.1f,
           float far = 100.0f,
           bool hmgDepth = bgfx::getCaps()->homogeneousDepth,
           const string& name = "Camera");

    void Start();

    void Update() override;

    void LookAt(Vector3& point);
    void LookAt(Vector3&& point);

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

    /**
     * Is homogeneous depth supported?
     */
    bool homogeneousDepth = bgfx::getCaps()->homogeneousDepth;
};

}

#endif //CORE_CAMERA_H
