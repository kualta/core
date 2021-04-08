#ifndef CORE_RENDERMANAGER_H
#define CORE_RENDERMANAGER_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

namespace core {


// TODO: refactoring needed
class RenderManager : public Singleton<RenderManager>, public Object {
public:

    RenderManager();
    ~RenderManager();
    static bool CreateRenderer(Window& window);
    static bool InitRenderer(Window& window);

    static bgfx::PlatformData GetPlatformData(const Window &window);

protected:

private:

};



}



#endif //CORE_RENDERMANAGER_H
