#ifndef CORE_RENDERMANAGER_H
#define CORE_RENDERMANAGER_H

#include "Essential.h"

#include "bgfx/bgfx.h"


namespace core {


// TODO: refactoring needed
class RenderManager : public Singleton<RenderManager>, public ObjectId {
public:

    RenderManager();
    ~RenderManager();
    static bool CreateRenderer(Window& window);
    static bool InitRenderer(Window& window);

    static bgfx::PlatformData GetPlatformData(Window& window);

protected:

private:

};



}



#endif //CORE_RENDERMANAGER_H
