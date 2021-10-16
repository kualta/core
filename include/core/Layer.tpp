#include "Logger.h"
#include <iomanip>

namespace core {

template<typename T>
void Layer::Link(T& obj) {
    assertSupportedType<T>();
    std::vector<T*>& container = GetContainerForType<T>();

    if (IsLinked(obj)) {
        Logger::Log(INTERNAL, WARN_HERE) << "Layer " << std::quoted(name) << " is already linked with " << obj.GetInfo();
        throw std::logic_error("Layer " + name + " is already linked with " + obj.GetInfo());
    }

    container.push_back(&obj);
}
template<typename T>
void Layer::Unlink(T& obj) {
    assertSupportedType<T>();
    std::vector<T*>& container = GetContainerForType<T>();

    container.erase(std::remove_if(container.begin(),
                                   container.end(),
                                   [&](T* e) { return *e == obj; }), container.end());
}
template<typename T>
bool Layer::IsLinked(T& obj) {
    assertSupportedType<T>();
    std::vector<T*>& container = GetContainerForType<T>();

    auto item = std::find(container.begin(), container.end(), &obj);
    return item != container.end() ? true : false;
}
template<typename T>
void Layer::assertSupportedType() {
    static_assert(std::is_same<Entity, T>::value
               || std::is_same<Camera, T>::value
               || std::is_same<Light, T> ::value,
                  "Cannot handle object of unsupported type");
}
template<typename T>
vector<T*>& Layer::GetContainerForType() {
    if constexpr(std::is_same<Entity, T>::value) { return entities; }
    if constexpr(std::is_same<Camera, T>::value) { return cameras; }
    if constexpr(std::is_same<Light, T> ::value) { return lights; }
}

}