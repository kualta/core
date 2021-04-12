#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::~Entity() {
    DestroyAllComponents();
}
void Entity::Spawn() {
    isActive = true;
}
void Entity::Despawn() {
    isActive = false;
}
void Entity::DestroyAllComponents() {
    for (auto c: components) { delete c; }
}

} // namespace core