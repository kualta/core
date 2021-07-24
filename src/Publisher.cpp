#include <core/Publisher.h>

namespace core {

void Publisher::SubscribeTo(const char* eventName, std::function<void()> callback) {
    if ( !this->HasEvent(eventName) ) {
        Logger::Log(GENERAL, ERR_HERE) << "Publisher does not have event \"" << eventName << "\"";
        throw std::runtime_error("Publisher does not have event \"" + string(eventName) + "\"");
    }

    auto e = std::find_if(eventList.begin(), eventList.end(), [&](event& e){ return e.first == eventName; });
    e->second.emplace_back(callback);
}
void Publisher::AddEvent(const string& name) {
    if (this->HasEvent(name)) {
        Logger::Log(GENERAL, WARN_HERE) << "Cannot add new event \"" << name
                                        << "\" to publisher: event with same name already exists";
        return;
    }

    eventList.emplace_back(name, callbackList { });
}
bool Publisher::HasEvent(const string &name) {
    auto a = std::find_if(eventList.begin(), eventList.end(), [&](event& e){ return e.first == name; });

    if (a != eventList.end()) {
        return true;
    } else {
        return false;
    }
}


}