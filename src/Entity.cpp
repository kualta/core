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
bool Entity::operator==(const Entity &rhs) const {
    return static_cast<const core::Object&>(*this) == static_cast<const core::Object&>(rhs) &&
           static_cast<const core::Node<core::Entity>&>(*this) == static_cast<const core::Node<core::Entity>&>(rhs) &&
           components == rhs.components &&
           isActive == rhs.isActive;
}
bool Entity::operator!=(const Entity &rhs) const {
    return !(rhs == *this);
}
void Entity::Destroy() {
    this->~Entity();
}
void Entity::Destroy(Entity& entity) {
    entity.Destroy();
}
void Entity::Update() {

}
void Entity::Draw() {

}

} // namespace core