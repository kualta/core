#include <core/Object.h>
#include <core/Logger.h>


namespace core {

uint32_t Object::objectCounter { 0 };

Object::Object(string name): id(++objectCounter), name(std::move(name)) {

}
Object::~Object() {
    Logger::Log(INFO, INTERNAL) << "Destroyed " << name << " object";
}
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