#include <core/Entity.h>

namespace core {


int16_t Entity::AddComponent(std::shared_ptr<Component> c) {
    components.push_back(c);
    return components.size() - 1;
}
void Entity::Spawn() {

}
void Entity::Despawn() {

}



} // namespace core