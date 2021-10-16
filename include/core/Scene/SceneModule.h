#ifndef CORE_SCENEMODULE_H
#define CORE_SCENEMODULE_H

#include "core/IModule.h"
#include "core/Entity.h"
#include "core/CameraList.h"

namespace core {

class SceneModule : public IModule {
public:
    SceneModule();

protected:

    void FixedTick() override;
    void EarlyTick() override;
    void Tick() override;
    void LateTick() override;

    CameraList cameraList { };

};


}


#endif //CORE_SCENEMODULE_H
