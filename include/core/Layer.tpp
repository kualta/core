/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#include "Logger.h"
#include <iomanip>

namespace core {

template<typename T>
void Layer::Link(T& obj) {
    assertSupportedType<T>();
    vector<T*>& container = GetContainerForType<T>();

    if (IsLinked(obj)) {
        Logger::Log(INTERNAL, WARN_HERE) << "Layer " << std::quoted(name) << " is already linked with " << obj.GetInfo();
        throw std::logic_error("Layer " + name + " is already linked with " + obj.GetInfo());
    }

    container.push_back(&obj);
}
template<typename T>
void Layer::Unlink(T& obj) {
    assertSupportedType<T>();
    vector<T*>& container = GetContainerForType<T>();

    container.erase(std::remove_if(container.begin(),
                                   container.end(),
                                   [&](T* e) { return *e == obj; }), container.end());
}
template<typename T>
bool Layer::IsLinked(T& obj) {
    assertSupportedType<T>();
    vector<T*>& container = GetContainerForType<T>();

    auto item = std::find(container.begin(), container.end(), &obj);
    return item != container.end();
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