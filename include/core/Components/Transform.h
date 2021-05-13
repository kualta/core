#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Vector.h>
#include "core/Essential.h"
#include "core/Component.h"

namespace core {

class Transform : public Component {
public:
    Transform() { }

    void Update();

protected:

private:
    Vector3 position { 0, 0, 0 };
    Vector3 rotatiton { 0, 0, 0 };
    Vector3 scale { 1, 1, 1 };
};


}

#endif //CORE_COMPONENT_TRANSFORM_H
