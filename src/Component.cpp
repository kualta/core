#include <core/Component.h>

namespace core {

Component::Component(Entity& parent, const string &name) : Object(name + " component"), parent(&parent) {

}
Component::~Component() {

}

}