#include <core/Entity.h>

namespace core {


int16_t Entity::AddComponent(const std::shared_ptr<Component>& c) {
    components.push_back(c);
    return components.size() - 1;
}
int32_t Entity::AddChild(const std::shared_ptr<Entity>& child) {
    children.push_back(child);
    return children.size() - 1;
}
void Entity::Spawn() {

}
void Entity::Despawn() {

}
void Entity::SetParent(const std::weak_ptr<Entity> &p) {
    parent = p;
    std::shared_ptr<Entity>(p)->AddChild(std::make_shared<Entity>(*this));
}


} // namespace core