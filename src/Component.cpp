#include <core/Component.h>

namespace core {

Component::Component(Entity *parent, const string& name) : Object(name + " component"), entity(parent) {

}
Component::~Component() {

}

void Component::Update() {

}

}