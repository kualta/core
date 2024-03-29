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
#ifndef CORE_SCENE_H
#define CORE_SCENE_H

#include "core/Essentials.h"
#include "core/NamedObjectContainer.h"
#include "core/Scene/SceneObject.h"


namespace core {

/**
 * Describes parent/child Entity relationships
 */
class Scene : public Object, public NamedObjectContainer<Scene> {
public:
    explicit Scene(const string& name);
    virtual ~Scene();

    /**
     * Get root entity of this scene
     * @return shared_ptr Entity
     */
    shared<Entity> Root();
    
    /**
     * Get current scene
     * @throws std::logic_error if no scene is set as current
     * @note Call to Scene::Get(name) implicitly sets first created scene as current
     */
    static Scene* GetCurrent();
    
    /**
     * Set scene as current
     */
    static void SetCurrent(const shared<Scene>& scene);
    
protected:
    
    /** Root Entity node */
    const shared<Entity> root;
    
    /** Current scene */
    static Scene* current;

};

}

#endif //CORE_SCENE_H
