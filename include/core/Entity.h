/**
 *  Check Entity.tpp for template definitions
 */
/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include "Essentials.h"
#include "Instantiable.h"
#include "IComponent.h"
#include "Object.h"
#include "Layer.h"
#include "IDrawable.h"
#include "Scene/Scene.h"
#include "Scene/SceneObject.h"

#include <memory>
#include <utility>
#include <vector>

namespace core {

/**
 *  Class of every object appearing on the scene.
 *  @note Not derivable, use Component system instead
 */
class Entity final : public Object, public ITicker, public SceneObject<Entity>, public Instantiable<Entity> {
public:
    explicit Entity(const string&    name = "Entity",
                    shared<Entity> parent = Scene::Get("Default")->Root(),
                    shared<Layer>   layer = Layer::Get("Default") );
    ~Entity() final;

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
     * Checks if entity has component of type T, required by component of type C, logs error & throws if it does not
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
     * Add this Entity to layer
     * @param name - Name of the layer
     */
    void SetLayer(const string& name);

    /**
     * Get Layer this entity is attached to
     * @return pointer to Layer
     */
    shared<Layer> GetLayer();
    
    /**
     * Destroys this entity and its children
     */
    static void Destroy(shared<Entity>& entity);


    bool operator==(const Entity &rhs) const;
    bool operator!=(const Entity &rhs) const;

protected:
    friend class SceneModule;
    friend class Layer;

    /** Passes FixedTick to all components of this entity */
    void Start() override;

    /** Passes FixedTick to all components of this entity */
    void FixedTick() override;

    /** Passes EarlyTick to all components of this entity */
    void EarlyTick() override;

    /** Passes Tick to all components of this entity */
    void Tick() override;

    /** Passes LateTick to all components of this entity */
    void LateTick() override;

    /** Passes FixedTick to all components of this entity */
    void Stop() override;


    struct ComponentsListing {
        vector<shared<IComponent>>  bases         { };
        vector<ITicker*>            tickers       { };
        vector<IDrawable*>          drawables     { };
    } components;

    shared<Layer> layer;
};

} // namespace core

#include "Entity.tpp"

#endif //INTERFACERS_ENTITY_H