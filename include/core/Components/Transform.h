#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include "core/Essential.h"
#include "core/Component.h"

namespace core {

class Transform : public Component {
public:
    Transform() {}

protected:

private:
    Vector3 position;
    Vector3 rotatiton;
    Vector3 scale;
};


}

#endif //CORE_COMPONENT_TRANSFORM_H
