/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <core/Publisher.h>

namespace core {

void Publisher::SubscribeTo(const char* name, const std::function<void()>& callback) {
    if ( !this->HasEvent(name) ) {
        Logger::Log(GENERAL, ERR_HERE) << "Publisher does not have GetEvent \"" << name << "\"";
        throw std::runtime_error("Publisher does not have GetEvent \"" + string(name) + "\"");
    }

    auto e = std::find_if(eventList.begin(), eventList.end(), [&](event& e) { return e.first == name; } );
    e->second.emplace_back(callback);
}
void Publisher::AddEvent(const string& name) {
    if (this->HasEvent(name)) {
        Logger::Log(GENERAL, WARN_HERE) << "Cannot add new GetEvent \"" << name << "\" to publisher: GetEvent with same name already exists";
        return;
    }

    eventList.emplace_back(name, callbackList { });
}
bool Publisher::HasEvent(const string &name) {
    auto a = std::find_if(eventList.begin(), eventList.end(), [&](event& e) { return e.first == name; } );
    return a != eventList.end() ? true : false;
}
void Publisher::Trigger(const string& name) {
    if ( !this->HasEvent(name) ) {
        Logger::Log(GENERAL, ERR_HERE) << "Publisher does not have GetEvent \"" << name << "\"";
        throw std::runtime_error("Publisher does not have GetEvent \"" + name + "\"");
    }

    auto e = std::find_if(eventList.begin(), eventList.end(), [&](event& e) { return e.first == name; } );
    for (const auto& callback : e->second) {
        callback();
    }
}


}