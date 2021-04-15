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
        Logger::Log(ERR, INTERNAL) << "Entity already has this component!";
        return *this;
    }

    T* component = new T();
    components.push_back(component);

    return *this;
}
template<typename T>
Entity& Entity::AddComponent(T c) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    if ( this->HasComponent<T>() ) {
        Logger::Log(ERR, INTERNAL) << "Entity already has this component!";
        return *this;
    }

    T* component = new T(c);

    components.push_back(component);
    return *this;
}
template<typename T>
T& Entity::GetComponent() {
    for (auto c: components) {
        if (typeid(c) == typeid(T)) {
            return *c;
        }
    }
    return nullptr;
}
template<typename T>
bool Entity::HasComponent() {
    if ( std::any_of(components.begin(),
                     components.end(),
                     [](auto &c){ return typeid(c) == typeid(T); }) )
    {
        return true;
    } else {
        return false;
    }
}

} // namespace core