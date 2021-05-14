#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include "core/Essential.h"
#include "core/Component.h"
#include <core/Math.h>
#include <core/Vector.h>
#include <core/Matrix.h>

namespace core {

class Transform : public Component {
public:
    Transform() { }

    void Update();

    Matrix4 transform { Matrix4::identity };
protected:
    void UpdateTransform();

private:

    Vector3 position { 0, 0, 0 };
    Vector3 rotatiton { 0, 0, 0 };
    Vector3 scale { 1, 1, 1 };
};


}

#endif //CORE_COMPONENT_TRANSFORM_H
