#ifndef CORE_PUBLISHER_H
#define CORE_PUBLISHER_H

#include "Essential.h"
#include "Logger.h"

#include <vector>
#include <utility>
#include <functional>
#include <unordered_set>

namespace core {

class Publisher {
public:

    void SubscribeTo(const char* name, std::function<void()> callback);
    bool HasEvent(const string& name);

protected:
    using callbackList = std::vector<std::function<void()>>;
    using event = std::pair<string, callbackList>;

    void AddEvent(const string& name);
    void Trigger(const string& name);

    std::vector<event> eventList;

};

}

#endif //CORE_PUBLISHER_H
