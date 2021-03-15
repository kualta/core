#include "Root.h"
#include <memory>

namespace core {


Root::Root() {
    logManager_ = std::make_unique<LogManager>();
    windowManager_ = std::make_unique<WindowManager>();
    renderManager_ = std::make_unique<RenderManager>();
    inputManager_ = std::make_unique<InputManager>();
    soundManager_ = std::make_unique<SoundManager>();
    networkManager_ = std::make_unique<NetworkManager>();
}
Root::~Root() {

}


}