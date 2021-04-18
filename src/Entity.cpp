#include <core/Entity.h>
#include <core/EntityPool.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(Entity *parent, std::vector<Component *> c)
        : Node<Entity>(parent), components(std::move(c)) {
}
Entity::~Entity() {
}
void Entity::Spawn() {
    isActive = true;
}
void Entity::Despawn() {
    isActive = false;
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
bool Entity::operator==(const Entity &rhs) const {
    return static_cast<const core::Object&>(*this) == static_cast<const core::Object&>(rhs) &&
           static_cast<const core::Node<core::Entity>&>(*this) == static_cast<const core::Node<core::Entity>&>(rhs) &&
           components == rhs.components &&
           isActive == rhs.isActive;
}

} // namespace core