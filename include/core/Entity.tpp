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
        Logger::Log(WARN, INTERNAL) << "Entity " << this->GetInfo() << ") already has this component!";
        return *this;
    }

    std::shared_ptr<T> component = std::make_shared<T>(*this);

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

    // Create a copy of provided component, to ensure heap allocation of all children
    std::shared_ptr<T> component = std::make_shared<T>(c);

    assertStandardComponents<T>(component.get());
    assertIncompatibleComponents<T>(component.get());

    components.push_back(std::move(component));
    return *this;
}
template<typename T, typename... Args>
Entity &Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    if ( this->HasComponent<T>() ) {
        Logger::Log(WARN, INTERNAL) << "Entity already has this component!";
        return *this;
    }

    // Create a copy of provided component, to ensure heap allocation of all children
    std::shared_ptr<T> component = std::make_shared<T>(args...);

    assertStandardComponents<T>(component.get());
    assertIncompatibleComponents<T>(component.get());

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
    return std::any_of(components.begin(),
                       components.end(),
                       [&](std::shared_ptr<Component> &c) { return typeid(*c).hash_code() == typeid(T).hash_code(); }
                       );
}
template<typename T>
void Entity::assertStandardComponents(Component* cPtr) {
    if (typeid(T) == typeid(Transform)) {
        transform = dynamic_cast<Transform*>(cPtr);
    }
    if (typeid(T) == typeid(Renderer)) {
        renderer = dynamic_cast<Renderer*>(cPtr);
    }
}
template<typename T>
void Entity::assertIncompatibleComponents(Component *cPtr) {
    if (typeid(T) == typeid(Renderer)) {
        if (!this->HasComponent<Transform>()) {
            Logger::Log(WARN, OBJECT) << "Entity " << GetInfo()
                                      << " does not have Transform component attached, but has Renderer!"
                                      << " Draw calls will result in error";
        }
    }
}

} // namespace core