#include "Event.h"

namespace core {

template<typename E, typename... args>
std::atomic<uint32_t> Event<E, args...>::eventCounter { 0 };

template<typename E, typename... args>
void Event<E, args...>::Subscribe(const std::function<void(E&, args...)>& callback) {
    callbacks.emplace_back(callback);
}
template<typename T, typename... Args>
void Event<T, Args...>::Trigger(T& obj, Args... args) {
    for (const auto& callback : callbacks) {
        callback(obj, args...);
    }
}

}
