#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <core/Essential.h>
#include <core/IComponent.h>
#include <core/Entity.h>
#include <core/Math.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>

namespace core {

class Camera : public IComponent, public SceneGraph::Camera3D {
public:
    explicit Camera(Entity&       parent,
                    float         fovY = 90.0f,
                    float        width = 600.0f,
                    float       height = 400.0f,
                    float    nearPlane = 0.1f,
                    float     farPlane = 100.0f,
                    const string& name = "Camera");

    void Tick() override;

protected:

    Matrix4 viewMatrix;
    Matrix4 projectionMatrix;

    /**
     * Point camera is pointing towards
     */
    Vector3 lookAt = Vector3(0);

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
