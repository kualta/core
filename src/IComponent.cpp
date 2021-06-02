#include <core/IComponent.h>

namespace core {

IComponent::IComponent(Entity& parent, const string& name) : Object(name + " component"), entity(&parent) {

}
IComponent::~IComponent() {

}

}