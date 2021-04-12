#include <core/Entity.h>

namespace core {


void Entity::Spawn() {

}
void Entity::Despawn() {

}
template<typename T>
void Entity::AddComponent() {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    T component = new T();
    components.push_back(component);
}
template<typename T>
void Entity::AddComponent(T c) {
    static_assert(std::is_base_of<core::Component, T>::value, "Component T must inherit from core::Component");

    components.push_back(c);
}
template<typename T>
T* Entity::GetComponent() {
    for (auto c: components) {
       if (typeid(c) == typeid(T::value_type)) {
            return c;
       }
    }
    return nullptr;
}

} // namespace core