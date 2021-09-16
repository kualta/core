#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(Entity& parent, const string& name, std::vector<std::shared_ptr<IComponent>> c)
: core::Object(name), GraphObject(&parent), components(std::move(c))
{

}
Entity::Entity(GraphObject* parent, const string &name, std::vector<std::shared_ptr<IComponent>> c)
: core::Object(name), GraphObject(parent), components(std::move(c))
{

}
Entity::~Entity() {

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