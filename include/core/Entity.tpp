/**
 *  core::Entity template function implementations file
 */

#include "Logger.h"
#include "Component.h"

namespace core {

template<typename T>
Entity& Entity::AddComponent() {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    if ( this->HasComponent<T>() ) {
        Logger::Log(WARN, INTERNAL) << "Entity already has this component!";
        return *this;
    }

    std::shared_ptr<T> component = std::make_shared<T>();

    assertStandardComponents<T>(component.get());

    components.push_back(std::move(component));

    return *this;
}
template<typename T>
Entity& Entity::AddComponent(T c) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    if ( this->HasComponent<T>() ) {
        Logger::Log(WARN, INTERNAL) << "Entity already has this component!";
        return *this;
    }

    // Create a copy of provided component, so that all children of Entitiy are allocated on heap.
    std::shared_ptr<T> component = std::make_shared<T>(c);

    assertStandardComponents<T>(component.get());

    components.push_back(std::move(component));
    return *this;
}
template<typename T>
T& Entity::GetComponent() {
    auto const& it = std::find_if(components.begin(), components.end(), [&](std::shared_ptr<T>& p)
    {
        return typeid(p) == typeid(T);
    });
    if ( it != components.back() ) {
        return *it;
    } else {
        return nullptr;
    }
}
template<typename T>
bool Entity::HasComponent() {
    if ( std::any_of(components.begin(),
                     components.end(),
                     [&](std::shared_ptr<Component> &c){ return typeid(c) == typeid(T); }) )
    {
        return true;
    } else {
        return false;
    }
}
template<typename T>
void Entity::assertStandardComponents(T* component) {
    if (typeid(T) == typeid(Transform)) {
        transform = component;
    }
    if (typeid(T) == typeid(Renderer)) {
        renderer = component;
    }
}

} // namespace core