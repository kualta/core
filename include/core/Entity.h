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
class Entity : public Object, public Node<Entity> {
public:
    Entity() : Node<Entity>(root) { }
    Entity(std::vector<Component*> c)
        : Node<Entity>(root), components(std::move(c)) { }
    Entity(Entity* parent, std::vector<Component*> c)
        : Node<Entity>(parent), components(std::move(c)) { }

    void Spawn();
    void Despawn();


    template<typename T> T* GetComponent();
    template<typename T> bool HasComponent();
    template<typename T> Entity& AddComponent();
    template<typename T> Entity& AddComponent(T c);

protected:
    std::vector<Component*> components;
};

} // namespace core



#endif //INTERFACERS_ENTITY_H
