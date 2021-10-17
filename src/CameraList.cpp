#include <core/CameraList.h>
#include <exception>

namespace core {

CameraList::CameraList() {

}

void CameraList::Register(Camera* camera) {
    cameras.push_back(camera);
}
void CameraList::Unregister(Camera* camera) {
    cameras.erase(std::find(cameras.begin(), cameras.end(), camera));
}
Camera* CameraList::GetGameViewCamera() {
    throw std::logic_error("Not yet implemented");
}
SceneCamera* CameraList::GetSceneViewCamera() {
    for (Camera* camera : cameras) {
        if (dynamic_cast<SceneCamera*>(camera)) return dynamic_cast<SceneCamera*>(camera);
    }
    return nullptr;
}

}