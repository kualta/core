#include <core/Modules/SceneModule.h>

namespace core {

SceneModule::SceneModule() : IModule("Scene") {
    Logger::Log(INFO, SCENE) << "Initialized Scene module";
}
SceneModule::~SceneModule() {
    Logger::Log(INFO, SCENE) << "Initialized Scene module";
}
void SceneModule::Update() {
    std::for_each(Entity::instances.begin(),
                  Entity::instances.end(),
                  [&] (Entity* e) { e->Update(); } );
}

}
