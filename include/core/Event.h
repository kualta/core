#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include "Essentials.h"

#include <vector>
#include <utility>
#include <functional>
#include <unordered_set>

namespace core {

template<typename T, typename ...Args>
class Event {
public:
    using callbackList = std::vector<std::function<void(T&, Args...)>>;

    void Subscribe(const std::function<void(T&, Args...)>& callback);
    void Trigger(T& obj, Args... args);

protected:

    callbackList callbacks;
    uint32_t id { ++eventCounter };

private:
    static std::atomic<uint32_t> eventCounter;
};

} // namespace core

#include "Event.tpp"

#endif //CORE_EVENT_H
