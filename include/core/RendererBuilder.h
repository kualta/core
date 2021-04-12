#ifndef CORE_RENDERERBUILDER_H
#define CORE_RENDERERBUILDER_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

namespace core {

class RendererBuilder : public Singleton<RendererBuilder>, public Object {
public:

    RendererBuilder();
    ~RendererBuilder();
    static bool CreateRenderer(Window& window);
    static bool Init(Window& window);

    static bgfx::PlatformData GetPlatformData(const Window &window);

protected:

private:

};



}



#endif //CORE_RENDERERBUILDER_H
