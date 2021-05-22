#include <core/Modules/SceneModule.h>

namespace core {

SceneModule::SceneModule() : IModule("Scene", SCENE) {

}
SceneModule::~SceneModule() {

}
void SceneModule::Tick() {
    std::for_each(Entity::instances.begin(),
                  Entity::instances.end(),
                  [&] (Entity* e) { e->Tick(); } );
}

}
