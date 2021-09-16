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
    explicit Camera(Entity&     parent,
                    float          fov = 90.0f,
                    float        width = 1280.0f,
                    float       height = 720.0f,
                    float     farPlane = 100.0f,
                    float    nearPlane = 0.1f,
                    const string& name = "Camera");

    void Tick() override;
    void Draw();

protected:

    Transform* transform;

    /** Field of View by Y axis */
    float fov = 90.0f;

    /** Width of camera rectangle */
    float width = 1280.0f;

    /**  Height of camera rectangle */
    float height = 720.0f;

    /** Camera boundaries aspect ratio */
    float aspectRatio = width / height;

    /** Near clipping plane distance */
    float nearPlane = 0.1f;

    /**  Far clipping plane distance */
    float farPlane = 100.0f;
};

}

#endif //CORE_CAMERA_H
