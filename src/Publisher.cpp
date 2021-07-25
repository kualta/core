#include <core/Publisher.h>

namespace core {

void Publisher::SubscribeTo(const char* name, std::function<void()> callback) {
    if ( !this->HasEvent(name) ) {
        Logger::Log(GENERAL, ERR_HERE) << "Publisher does not have event \"" << name << "\"";
        throw std::runtime_error("Publisher does not have event \"" + string(name) + "\"");
    }

    auto e = std::find_if(eventList.begin(), eventList.end(), [&](event& e){ return e.first == name; });
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
void Publisher::Trigger(const string& name) {
    if ( !this->HasEvent(name) ) {
        Logger::Log(GENERAL, ERR_HERE) << "Publisher does not have event \"" << name << "\"";
        throw std::runtime_error("Publisher does not have event \"" + string(name) + "\"");
    }

    auto e = std::find_if(eventList.begin(), eventList.end(), [&](event& e){ return e.first == name; });
    for (const auto& callback : e->second) {
        callback();
    }
}


}