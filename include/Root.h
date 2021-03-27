#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include <memory>
#include <vector>

#include "Singleton.h"
#include "ObjectId.h"
#include "LogManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "NetworkManager.h"
#include "WindowPool.h"


namespace core {


class Root : public Singleton<Root>, public ObjectId {

public:
    Root();
    ~Root();

    const std::unique_ptr<LogManager> &GetLogManager() const;
    const std::unique_ptr<RenderManager> &GetRenderManager() const;
    const std::unique_ptr<SoundManager> &GetSoundManager() const;
    const std::unique_ptr<NetworkManager> &GetNetworkManager() const;

protected:
    std::unique_ptr<LogManager> logManager;
    std::unique_ptr<WindowPool> windowPool;
    std::unique_ptr<RenderManager> renderManager;
    std::unique_ptr<SoundManager> soundManager;
    std::unique_ptr<NetworkManager> networkManager;

private:
};


}


#endif //CORE_ROOT_H
