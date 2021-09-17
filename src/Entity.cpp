#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(const string& name, GraphObject* parent, ComponentsContainer c)
: core::Object(name), GraphObject(parent), components(std::move(c))
{

}
bool Entity::operator!=(const Entity &rhs) const {
    return !(rhs == *this);
}
void Entity::Tick() {
    std::for_each(components.begin(),
                  components.end(),
                  [&](std::shared_ptr<IComponent> &c) {
        c->Tick();
    });
}
bool Entity::operator==(const Entity &rhs) const {
    return this->GetId() == rhs.GetId();
}

} // namespace core