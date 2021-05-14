#include <core/Component.h>

namespace core {

Component::Component(Entity &entity) : entity(&entity) {

}
Component::~Component() {

}

}