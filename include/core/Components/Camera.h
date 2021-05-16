#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <core/Essential.h>
#include <core/Component.h>

#include <core/Entity.h>
#include <bx/math.h>

namespace core {

class Camera : Component {
public:
    Camera(Entity& parent);

    void Update() override;

    Matrix4 view;
    Matrix4 proj;

protected:

};

}

#endif //CORE_CAMERA_H
