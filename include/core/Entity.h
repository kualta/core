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
    Entity()
        : Node<Entity>(root) { }
    Entity(std::vector<Component*> c)
        : Node<Entity>(root), components(std::move(c)) { }
    Entity(Entity* parent, std::vector<Component*> c)
        : Node<Entity>(parent), components(std::move(c)) { }

    ~Entity();

    void Spawn();
    void Despawn();

    /**
     * Get attached to this entity component
     * @tparam T - component typename
     * @return Reference to component if it exists in Entity, nullptr otherwise
     * @note Use Entity::HasComponent<T>() to make sure component exists
     */
    template<typename T> T& GetComponent();

    /**
     * Does entity have this component?
     * @tparam T - component typename
     * @return true if Entity contains component
     * @return false if Entity doesn't contain component
     */
    template<typename T> bool HasComponent();

    /**
     * Creates new Component of type T and adds it to Entity
     * @tparam T - new component typename
     * @return Reference to this Entity
     * @warning T must inherit from core::Component
     * @note Method chaining is possible
     */
    template<typename T> Entity& AddComponent();

    /**
     * Adds existing Component c to Entity
     * @tparam T - component typename
     * @return Reference to this Entity
     * @warning T must inherit from core::Component
     * @note Method chaining is possible
     */
    template<typename T> Entity& AddComponent(T c);

    /**
     * Destroys all Components in this Entity
     */
    void DestroyAllComponents();

protected:
    std::vector<Component*> components;
};

} // namespace core



#endif //INTERFACERS_ENTITY_H
