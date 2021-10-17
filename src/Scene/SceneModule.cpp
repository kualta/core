#include <core/Scene/SceneModule.h>

namespace core {

SceneModule::SceneModule()
: IModule("Scene", SCENE)
{

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
