#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include <memory>
#include <utility>
#include <vector>
#include "Essential.h"
#include "Component.h"
#include "Object.h"
#include "Node.h"

namespace core {


/**
 *  Base class for every object appearing on the scene.
 */
class Entity : public Object, public Node {
public:
    Entity() {}
    Entity(std::vector<std::shared_ptr<Component>> c) {}

    void Spawn();
    void Despawn();

protected:

private:
};

} // namespace core



#endif //INTERFACERS_ENTITY_H
