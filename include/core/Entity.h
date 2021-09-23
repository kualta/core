/**
 *  Check Entity.tpp for template definitions
 */
#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include "Essentials.h"
#include "Instantiable.h"
#include "IComponent.h"
#include "Object.h"
#include "Scene.h"
#include "ScriptedBehaviour.h"

#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>

#include <memory>
#include <utility>
#include <vector>

namespace core {

typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> GraphObject;
typedef std::vector<std::shared_ptr<core::IComponent>> ComponentsContainer;

/**
 *  Class of every object appearing on the scene.
 *  @note Not derivable, use Component system instead
 */
class Entity final : public Object, public GraphObject, public ITicker, public Instantiable<Entity> {
public:
    explicit Entity(const string& name = "Entity", GraphObject* parent = Scene::Get(), ComponentsContainer c = { });

    /** Passes FixedTick to all components of this entity */
    void FixedTick() override;

    /** Passes EarlyTick to all components of this entity */
    void EarlyTick() override;

    /** Updates all components of this entity */
    void Tick() override;

    /** Passes LateTick to all components of this entity */
    void LateTick() override;

    /**
     * Creates new Component c and adds it to Entity,
     * passing additional arguments to the component's constructor
     * @details Method chaining is possible
     * @tparam T - component typename
     * @tparam Args - Arguments passed to Component's constructor
     * @return Reference to this Entity, allowing method chaining
     */
    template<typename T, typename ...Args>
    Entity& AddComponent(Args... args);

    /**
     * Creates new Component c and adds it to Entity,
     * passing additional arguments to the component's constructor
     * @details Method chaining is possible
     * @tparam T - Component template typename
     * @tparam S - Component typename
     * @tparam Args - Arguments passed to Component's constructor
     * @return Reference to this Entity, allowing method chaining
     */
    template<template<typename> typename T, typename S, typename ...Args>
    Entity& AddComponent(Args... args);

    /**
     * Get attached to this entity component
     * @tparam T - Component typename
     * @return Component* if Entity has it, nullptr otherwise
     * @note Use Entity::HasComponent<T>() to make sure component exists
     */
    template<typename T>
    T* GetComponent();

    /**
     * Does entity have this component?
     * @tparam T - Component typename
     * @return true if Entity contains component
     * @return false if Entity doesn't contain component
     */
    template<typename T>
    bool HasComponent();

    /**
     * Checks if entity has component of type T, required by component of type C,
     * logs error & throws if it does not
     * @param caller - Pointer to calling component
     * @throw std::logic_error, if does not contain needed component
     */
    template<typename T, typename C>
    void assertRequiredComponent(C* caller);

    /**
     * Checks if entity has component of type T, logs error & throws if it does
     * @param caller - Pointer to calling component
     * @throw std::logic_error, if Entity already has Component T
     */
    template<typename T>
    void assertExistingComponent();

    /**
     * Imports and adds Entities from the file to the scene
     * @param filepath - path to model file
     */
    static vector<shared<Entity>> Load(const string& filepath);


    bool operator==(const Entity &rhs) const;
    bool operator!=(const Entity &rhs) const;

protected:

    ComponentsContainer components;

};

} // namespace core

#include "Entity.tpp"

#endif //INTERFACERS_ENTITY_H