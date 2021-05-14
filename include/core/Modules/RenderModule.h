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

    void Update() override;

protected:
    RenderModule();
    ~RenderModule();

};


}

#endif //CORE_RENDERMODULE_H