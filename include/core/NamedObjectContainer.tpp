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
#ifndef CORE_NAMEDOBJECTCONTAINER_TPP
#define CORE_NAMEDOBJECTCONTAINER_TPP

#include "core/NamedObjectContainer.h"
#include "core/Logger.h"

#include <iomanip>

namespace core {

template<typename T>
vector<shared<T>> NamedObjectContainer<T>::container { };

template<typename T>
bool NamedObjectContainer<T>::Exists(const string& name) {
    return std::any_of(container.begin(), container.end(), [&](shared<T>& obj) { return obj->GetName() == name; });
}
template<typename T>
void NamedObjectContainer<T>::Delete(const string& name) {
    NamedObjectContainer<T>::Get(name).reset;
}
template<typename T>
shared<T> NamedObjectContainer<T>::Create(const string& name) {
    if (Exists(name)) {
        Logger::Log(INTERNAL, ERR_HERE) << "Object " << name << " already exists";
        throw std::logic_error("Object " + name + " already exists");
    }
    Logger::Log(INTERNAL, DEBUG) << "Creating new object " << std::quoted(name);
    
    shared<T> obj = make_shared<T>(name);
    container.push_back(std::move(obj));
    return container.back();
}
template<typename T>
shared<T> NamedObjectContainer<T>::Get(const string& name) {
    auto item = std::find_if(container.begin(), container.end(), [&](shared<T>& o) { return o->GetName() == name; });
    if (item != container.end()) {
        return *item;
    } else {
        return Create(name);
    }
}

}

#endif //CORE_NAMEDOBJECTCONTAINER_TPP
