#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include <memory>
#include <utility>
#include <vector>
#include "Essential.h"
#include "Component.h"
#include "Object.h"

namespace core {


/**
 *  Base class for every object appearing on the scene.
 */
class Entity : public Object {
public:
    Entity() {}
    Entity(std::vector<std::shared_ptr<Component>> c) : components(std::move(c)) {}

    int16_t AddComponent(std::shared_ptr<Component> c);
    void Spawn();
    void Despawn();

protected:
    std::weak_ptr<Entity> parent;
    std::vector<std::shared_ptr<Entity>> children;
    std::vector<std::shared_ptr<Component>> components;

private:
};

} // namespace core



#endif //INTERFACERS_ENTITY_H
