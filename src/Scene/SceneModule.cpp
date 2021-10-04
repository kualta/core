#include <core/Scene/SceneModule.h>

namespace core {

SceneModule::SceneModule() : IModule("Scene", SCENE) {

}
void SceneModule::FixedTick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(), [&](Entity* e) { e->FixedTick(); } );
}
void SceneModule::EarlyTick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(), [&](Entity* e) { e->EarlyTick(); } );
}
void SceneModule::Tick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(), [&](Entity* e) { e->Tick(); } );
}
void SceneModule::LateTick() {
    std::for_each(Entity::instances.begin(), Entity::instances.end(), [&](Entity* e) { e->LateTick(); } );
}

}
