/**
 * Check SceneObject.tpp for template difinitions.
 */
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
#ifndef CORE_SCENEOBJECT_H
#define CORE_SCENEOBJECT_H

#include "core/Essentials.h"

namespace core {

/**
 * Manages Scene Graph parent/child relationships
 */
template<typename T>
class SceneObject {
public:
    SceneObject(shared<T> parent);
    virtual ~SceneObject();
    
    /**
     * Get shared ptr to parent
     * @return shared ptr to parent if exists, nullptr otherwise
     */
    shared<T> GetParent();
    
    /**
     * Get reference to all children array
     */
    vector<shared<T>>& GetChildren();
    
    /**
     * Sets object as current parent
     */
    void SetParent(shared<T> newParent);
    
    /**
     * Recursively derstroy all children
     * @details calls shared<T>::reset on every child object
     */
    void DestroyChildren();

protected:
    
    /** Pointer to current parent */
    weak<T> parent;
    
    /** Vector of all children of this object */
    vector<shared<T>> children;

};

} // namespace core

#include "SceneObject.tpp"

#endif //CORE_SCENEOBJECT_H
