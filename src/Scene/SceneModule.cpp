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
#include <core/Scene/SceneModule.h>

namespace core {

SceneModule::SceneModule()
: IModule("Scene", SCENE)
{
    defaultScene = Scene::Get("Default");
}
void SceneModule::Start() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(),   [&](Entity* e) { e->Start(); } );
}
void SceneModule::EarlyTick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(),   [&](Entity* e) { e->EarlyTick(); } );
}
void SceneModule::FixedTick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(),   [&](Entity* e) { e->FixedTick(); } );
}
void SceneModule::Tick() {
    std::for_each(Entity::instances.begin(),  Entity::instances.end(),  [&](Entity* e) { e->Tick(); } );

    /** Make Camera->Draw() call only after all entities were updated */
    std::for_each(cameraList.cameras.begin(), cameraList.cameras.end(), [&](Camera* camera) { camera->Draw(); });
}
void SceneModule::LateTick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(),   [&](Entity* e) { e->LateTick(); } );
}
void SceneModule::Stop() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(),   [&](Entity* e) { e->Stop(); } );
}

}
