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
#include <core/Scene/Scene.h>
#include <core/Entity.h>

namespace core {

shared<Scene> Scene::current { nullptr };

Scene::Scene(const string& name)
: Object(name), root(std::make_shared<Entity>("Root", nullptr))
{
    if (!current) { current = shared<Scene>(this); }
}
const shared<Entity>& Scene::Root() {
    return root;
}
shared<Scene> Scene::GetCurrent() {
    if (!current) {
        Logger::Log(SCENE, ERR) << "No available scene found";
        throw std::logic_error("No available scene found");
    }
    return current;
}
void Scene::SetCurrent(const shared<Scene>& scene) {
    current = scene;
}

}