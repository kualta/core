#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include <memory>
#include <vector>

#include "Singleton.h"
#include "ObjectId.h"
#include "LogManager.h"
#include "WindowManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "NetworkManager.h"


namespace core {


class Root : public Singleton<Root>, public ObjectId {

public:
    Root();
    ~Root();

protected:
    std::unique_ptr<LogManager> logManager;
    std::unique_ptr<WindowManager> windowManager;
    std::unique_ptr<RenderManager> renderManager;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<SoundManager> soundManager;
    std::unique_ptr<NetworkManager> networkManager;

private:
};


}


#endif //CORE_ROOT_H
