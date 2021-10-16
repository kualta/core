#include <core/CameraList.h>

namespace core {

CameraList::CameraList() {

}

void CameraList::Register(Camera* camera) {
    cameras.push_back(camera);
}
void CameraList::Unregister(Camera* camera) {
    cameras.erase(std::find(cameras.begin(), cameras.end(), camera));
}

}