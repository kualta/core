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
    bool CreateRenderer(Window& window);
    bool InitRenderer(Window& window);

    static bgfx::PlatformData GetPlatformData(Window& window);

protected:

private:

};



}



#endif //CORE_RENDERMANAGER_H
