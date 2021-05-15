#ifndef CORE_RENDERMODULE_H
#define CORE_RENDERMODULE_H

#include <core/Essential.h>
#include <core/IModule.h>
#include <core/Components/Renderer.h>

#include <algorithm>
#include <bgfx/bgfx.h>

namespace core {

class RenderModule : public IModule {
public:
    RenderModule();
    ~RenderModule();

    void Update() override;

protected:

};


}

#endif //CORE_RENDERMODULE_H
