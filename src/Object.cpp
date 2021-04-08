#include <core/Object.h>

namespace core {

    uint32_t Object::objectCounter {0 };

void Object::Destroy(Object obj) {
    // TODO: To be implemented
}

bool Object::operator==(const Object &rhs) const {
    return id == rhs.id;
}

bool Object::operator!=(const Object &rhs) const {
    return !(rhs == *this);
}

uint32_t Object::GetId() const {
    return id;
}

}