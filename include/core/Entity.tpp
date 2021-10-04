/**
 *  core::Entity template function implementations file
 */

#include "Logger.h"
#include "IComponent.h"
#include "Entity.h"


namespace core {

template<template<typename> typename T, typename S, typename ...Args>
Entity& Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<core::IComponent, T<S>>::value, "Component S must inherit from core::IComponent");

    // Create a copy of provided component, to ensure heap allocation of all children
    std::shared_ptr<T<S>> component = std::make_shared<T<S>>(*this, args...);

    components.push_back(std::move(component));
    return *this;
};
template<typename T, typename... Args>
Entity& Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<core::IComponent, T>::value, "Component T must inherit from core::IComponent");

    // Create a copy of provided component, to ensure heap allocation of all children
    auto component = std::make_shared<T>(*this, args...);

    components.push_back(std::move(component));
    return *this;
}
template<typename T, typename C>
void Entity::assertRequiredComponent(C* caller) {
    static_assert(std::is_base_of<core::IComponent, T>::value, "Component T must inherit from core::IComponent");
    static_assert(std::is_base_of<core::IComponent, C>::value, "Component C must inherit from core::IComponent");
    if ( !this->HasComponent<T>() ) {
        Logger::Log(OBJECT, ERR_HERE) << "Entity " << this->GetInfo() << " does not have component " << typeid(T).name() << ", required by " << caller->GetInfo();
        throw std::logic_error("Entity " + this->GetInfo() + " does not have component " + typeid(T).name() + ", required by " + caller->GetInfo());
    }
}
template<typename T>
void Entity::assertExistingComponent() {
    static_assert(std::is_base_of<core::IComponent, T>::value, "Component T must inherit from core::Component");
    if ( this->HasComponent<T>() ) {
        Logger::Log(OBJECT, ERR_HERE) << "Entity " << this->GetInfo() << " already has component " << typeid(T).name();
        throw std::logic_error("Entity " + this->GetInfo() + " already has component " + typeid(T).name());
    }
}

template<typename T>
T* Entity::GetComponent() {
    auto it = std::find_if(components.begin(),
                           components.end(),
                           [&](std::shared_ptr<IComponent> const& p) {
                               return typeid(*p).hash_code() == typeid(T).hash_code();
                           });
    if ( it != components.end() ) {
        return dynamic_cast<T*>(it->get());
    } else {
        return nullptr;
    }
}
template<typename T>
bool Entity::HasComponent() {
    return std::any_of(components.begin(), components.end(),
                       [&](std::shared_ptr<IComponent> &c) { return typeid(*c).hash_code() == typeid(T).hash_code(); } );
}

} // namespace core