#ifndef CORE_CAMERALIST_H
#define CORE_CAMERALIST_H

#include "Essentials.h"
#include "Singleton.h"
#include "Components/Camera.h"

namespace core {

class CameraList : public Singleton<CameraList> {
public:

    SceneCamera* GetSceneViewCamera();
    Camera* GetGameViewCamera();

protected:
    friend class SceneModule; // < Construction only allowed from SceneModule
    friend class Camera;      // < Registration only allowed from Camera

    CameraList();

    /** Add camera to Camera List */
    void Register(Camera* camera);

    /** Remove camera from Camera List */
    void Unregister(Camera* camera);

    std::vector<Camera*> cameras { };

};

}

#endif //CORE_CAMERALIST_H
