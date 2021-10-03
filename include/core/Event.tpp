#include "Event.h"

namespace core {

template<typename T, typename... Args>
std::atomic<uint32_t> Event<T, Args...>::eventCounter { 0 };

template<typename T, typename... Args>
void Event<T, Args...>::Subscribe(std::function<void(T&, Args...)> callback) {
    callbacks.emplace_back(callback);
}
template<typename T, typename... Args>
void Event<T, Args...>::Trigger(T& obj, Args... args) {
    for (const auto& callback : callbacks) {
        callback(obj, args...);
    }
}

}
