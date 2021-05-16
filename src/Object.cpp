#include <core/Object.h>
#include <core/Logger.h>


namespace core {

uint32_t Object::objectCounter { 0 };

Object::Object(string name): id(++objectCounter), name(std::move(name)) {
    Logger::Log(INFO, OBJECT) << "Created object " << GetInfo();
}
Object::~Object() {
    Logger::Log(INFO, OBJECT) << "Destroyed " << GetInfo() << " object";
}
uint32_t Object::GetId() const {
    return id;
}
string Object::GetInfo() const {
    return "\"" + name + "\""  + " ID(" + std::to_string(GetId()) + ")";
}
bool Object::operator==(const Object &rhs) const {
    return id == rhs.id;
}
bool Object::operator!=(const Object &rhs) const {
    return !(rhs == *this);
}

}