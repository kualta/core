#include <core/Object.h>

namespace core {

uint32_t Object::objectCounter { 0 };

uint32_t Object::GetId() const {
    return id;
}
void Object::Destroy() {
    this->~Object();
}
void Object::Destroy(Object& obj) {
    obj.Destroy();
}
bool Object::operator==(const Object &rhs) const {
    return id == rhs.id;
}
bool Object::operator!=(const Object &rhs) const {
    return !(rhs == *this);
}

}