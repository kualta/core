#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(string name, std::weak_ptr<Entity>& parent, std::vector<std::shared_ptr<Component>> c)
    : Object(std::move(name)), Node<Entity>(parent), components(std::move(c)) {
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
    return static_cast<const core::Object&>(*this).GetId() == static_cast<const core::Object&>(rhs).GetId();
}

string Entity::GetInfo() {
    return name + " ID(" + std::to_string(GetId()) + ")";
}

} // namespace core