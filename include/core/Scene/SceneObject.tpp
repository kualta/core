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
#ifndef CORE_SCENEOBJECT_TPP
#define CORE_SCENEOBJECT_TPP

#include "SceneObject.h"

namespace core {

template<typename T>
SceneObject<T>::SceneObject(const shared<T>& parent)
{
}
template<typename T>
SceneObject<T>::~SceneObject() {

}
template<typename T>
shared<T>& SceneObject<T>::GetParent() {
    return parent;
}
template<typename T>
vector<shared<T>>& SceneObject<T>::GetChildren() {
    return children;
}
template<typename T>
void SceneObject<T>::SetParent(const shared<T>& newParent) {
}
template<typename T>
void SceneObject<T>::DestroyChildren() {
    for (auto& child : children) {
        child->DestroyChildren();
        child.reset();
    }
}

}

#endif //CORE_SCENEOBJECT_TPP
