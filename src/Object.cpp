#include <core/Object.h>
#include <core/Logger.h>


namespace core {

std::atomic<uint32_t> Object::objectCounter { 0 };

Object::Object(string name)
: name(std::move(name)), id(++objectCounter)
{
    Logger::Log(OBJECT, INFO) << "Created object " << GetInfo();
}
Object::~Object() {
    Logger::Log(OBJECT, INFO) << "Destroyed object " << GetInfo();
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
    return !(id == rhs.id);
}

}