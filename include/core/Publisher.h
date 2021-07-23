#ifndef CORE_PUBLISHER_H
#define CORE_PUBLISHER_H

#include "Essential.h"

#include <vector>
#include <utility>
#include <functional>

namespace core {

class Publisher {
public:

    void SubscribeTo(const char* eventName, std::function<void()> callback);

protected:
    using callbackList = std::vector<std::function<void()>>;
    using event = std::pair<std::string, callbackList>;

    std::vector<event> eventList;

};

}

#endif //CORE_PUBLISHER_H
