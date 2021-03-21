#ifndef CORE_RENDERMANAGER_H
#define CORE_RENDERMANAGER_H

#include "Singleton.h"
#include "ObjectId.h"
#include "Window.h"


namespace core {


class RenderManager : public Singleton<RenderManager>, public ObjectId {
public:

    RenderManager();
    ~RenderManager();
    bgfx::PlatformData GetPlatformData(Window& window);
    bool CreateRenderer(Window& window);

protected:

private:

};



}



#endif //CORE_RENDERMANAGER_H
