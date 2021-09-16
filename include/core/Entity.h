/**
 *  Check Entity.tpp for template definitions
 */
#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include "Essential.h"
#include "Instantiable.h"
#include "IComponent.h"
#include "Object.h"
#include "Node.h"
#include "Scene.h"
#include "ScriptBehaviour.h"

#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>

#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>

#include <memory>
#include <utility>
#include <vector>

namespace core {

typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> GraphObject;

/**
 *  Base class for every object appearing on the scene.
 */
class Entity : public Object, public GraphObject, public Instantiable<Entity> {
public:
    Entity(Entity& parent,
           const string& name = "entity",
           std::vector<std::shared_ptr<IComponent>> c = { });
    Entity(GraphObject* parent = Scene::Get(),
           const string& name = "entity",
           std::vector<std::shared_ptr<IComponent>> c = { });
    ~Entity();

    /**
     * Updated all components of this entity
     */
    void Tick();

    /**
     * Creates new Component c and adds it to Entity,
     * passing additional arguments to the component's constructor
     * @details Method chaining is possible
     * @tparam T - component typename
     * @tparam Args - additional arguments
     * @return Reference to this Entity
     */
    template<typename T, typename ...Args>
    Entity& AddComponent(Args... args);

    template<template<typename> typename T, typename S, typename ...Args>
    Entity& AddComponent(Args... args);

    /**
     * Get attached to this entity component
     * @tparam T - component typename
     * @return Reference to component if it exists in Entity, nullptr otherwise
     * @note Use Entity::HasComponent<T>() to make sure component exists
     */
    template<typename T>
    T* GetComponent();

    /**
     * Does entity have this component?
     * @tparam T - component typename
     * @return true if Entity contains component
     * @return false if Entity doesn't contain component
     */
    template<typename T>
    bool HasComponent();

    // FIXME: these asserts require rethinking
    /**
     * Checks if entity has component of type T, required by component of type C, logs error if it does not
     * @param caller - Pointer to calling component
     * @return bool
     */
    template<typename T, typename C>
    void assertRequiredComponent(C* caller);

    /**
     * Checks if entity has component of type T, logs error if it does
     * @param caller - Pointer to calling component
     * @return bool
     */
    template<typename T>
    void assertExistingComponent();

    bool operator==(const Entity &rhs) const;
    bool operator!=(const Entity &rhs) const;

protected:

    std::vector<std::shared_ptr<IComponent>> components;
    bool  isActive { true };
};

} // namespace core


#include "Entity.tpp"


#endif //INTERFACERS_ENTITY_H