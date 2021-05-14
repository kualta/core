/**
 *  Check Entity.tpp for template definitions
 */
#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include "Essential.h"
#include "Instantiable.h"
#include "Component.h"
#include "Object.h"
#include "Node.h"
#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>

#include <memory>
#include <utility>
#include <vector>

namespace core {


/**
 *  Base class for every object appearing on the scene.
 */
class Entity : public Object, public Node<Entity>, public Instantiable<Entity> {
public:
    Entity(string name                               = "entity",
           std::weak_ptr<Entity>& parent             = root,
           std::vector<std::shared_ptr<Component>> c = { } );
    ~Entity();

    void Update();

    void Draw();

    /**
     * Activates entity
     * @note Entity is active by default, no need to call this after creation
     */
    void Spawn();

    /**
     * Deactivates entity
     * @note This method doesn't destroy entity
     */
    void Despawn();

    /**
     * Get attached to this entity component
     * @tparam T - component typename
     * @return Reference to component if it exists in Entity, nullptr otherwise
     * @note Use Entity::HasComponent<T>() to make sure component exists
     */
    template<typename T>
    T& GetComponent();

    /**
     * Does entity have this component?
     * @tparam T - component typename
     * @return true if Entity contains component
     * @return false if Entity doesn't contain component
     */
    template<typename T>
    bool HasComponent();

    /**
     * Creates new Component of type T and adds it to Entity
     * @tparam T - new component typename
     * @return Reference to this Entity
     * @warning returns *this even if component already exists
     * @note Method chaining is possible
     */
    template<typename T>
    Entity& AddComponent();

    /**
     * Adds existing Component c to Entity
     * @tparam T - component typename
     * @return Reference to this Entity
     * @warning returns *this even if component already exists
     * @note Method chaining is possible
     */
    template<typename T>
    Entity& AddComponent(T c);

    /**
     * Checks if component is of any standard components type
     * i.e. Transform or Renderer, if so sets member pointer to this component
     * @tparam T - Type of component
     * @param c - ptr to component
     */
    template<typename T>
    void assertStandardComponents(T* c);

    /**
     * Destroys this entity
     */
    void Destroy() override;

    /**
     * Destroys entity
     */
    static void Destroy(Entity& entity);

    string GetInfo();

    bool operator==(const Entity &rhs) const;
    bool operator!=(const Entity &rhs) const;

    Transform*                              transform { nullptr };
    Renderer*                               renderer  { nullptr };

protected:

    std::vector<std::shared_ptr<Component>> components;
    bool                                    isActive { true };
};

} // namespace core


#include "Entity.tpp"


#endif //INTERFACERS_ENTITY_H
