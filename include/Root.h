#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include <memory>
#include <vector>
#include "core.h"
#include "Singleton.h"

namespace core {


class Root : public Singleton<Root> {

public:
    Root();
    ~Root();

protected:
    std::vector<std::shared_ptr<Window>> windowsPool_;

    std::unique_ptr<LogManager> logManager_;
    std::unique_ptr<WindowManager> windowManager_;
    std::unique_ptr<RenderManager> renderManager_;
    std::unique_ptr<InputManager> inputManager_;
    std::unique_ptr<SoundManager> soundManager_;
    std::unique_ptr<NetworkManager> networkManager_;

private:
};


}


#endif //CORE_ROOT_H
