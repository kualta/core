/**
 *  core::Entity template function implementations file
 */

#include "Logger.h"
#include "Component.h"

namespace core {

template<typename T, typename... Args>
Entity &Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    // Create a copy of provided component, to ensure heap allocation of all children
    std::shared_ptr<T> component = std::make_shared<T>(*this, args...);

    components.push_back(std::move(component));
    return *this;
}
template<typename T, typename C>
bool Entity::assertRequiredComponent(C* caller) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");
    static_assert(std::is_base_of<core::Component, C>::value, "Component C must inherit from core::Component");

    if ( !this->HasComponent<T>() ) {
        Logger::Log(ERR, OBJECT) << "Entity " << this->GetInfo() << " does not have component "
                                          << typeid(T).name() << ", required by " << caller->GetInfo();
        return false;
    } else {
        return true;
    }
}
template<typename T>
bool Entity::assertExistingComponent() {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    if ( this->HasComponent<T>() ) {
        Logger::Log(ERR, OBJECT) << "Entity " << this->GetInfo() << " already has component "
                                          << typeid(T).name();
        return true;
    } else {
        return false;
    }
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
    return std::any_of(components.begin(),
                       components.end(),
                       [&](std::shared_ptr<Component> &c) { return typeid(*c).hash_code() == typeid(T).hash_code(); }
                       );
}

} // namespace core