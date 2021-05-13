#include <core/Modules/SceneModule.h>

namespace core {

SceneModule::SceneModule() : IModule("Scene", SCENE) {

}
SceneModule::~SceneModule() {

}
void SceneModule::Update() {
    std::for_each(Entity::instances.begin(),
                  Entity::instances.end(),
                  [&] (Entity* e) { e->Update(); } );
}

}
