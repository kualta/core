#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(const string& name, std::weak_ptr<Entity>& parent, std::vector<std::shared_ptr<Component>> c)
    : Object(name), Node<Entity>(parent), components(std::move(c)) {
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
void Entity::Update() {
    std::for_each(components.begin(),
                  components.end(),
                  [&](std::shared_ptr<Component> &c) {
        c->Tick();
    });
}
void Entity::Draw() {

}
bool Entity::operator==(const Entity &rhs) const {
    return static_cast<const core::Object&>(*this).GetId() == static_cast<const core::Object&>(rhs).GetId();
}

} // namespace core