#ifndef CORE_SCENEMODULE_H
#define CORE_SCENEMODULE_H

#include <core/IModule.h>
#include <core/Entity.h>

namespace core {

class SceneModule : public IModule {
public:
    SceneModule();

    void FixedTick() override;
    void EarlyTick() override;
    void Tick() override;
    void LateTick() override;
};

}


#endif //CORE_SCENEMODULE_H