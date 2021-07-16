#ifndef CORE_BGFXRENDERMODULE_H
#define CORE_BGFXRENDERMODULE_H

#include <core/Essential.h>
#include <core/IModule.h>
#include <core/Components/BgfxRenderer.h>
#include <core/Modules/IRenderModule.h>

#include <algorithm>
#include <bgfx/bgfx.h>

namespace core {

typedef BgfxRenderModule RenderModule;

class BgfxRenderModule : public IRenderModule {
public:
    BgfxRenderModule(InputModule *inputModule);
    ~BgfxRenderModule();

    void Frame() override;

};


}

#endif //CORE_BGFXRENDERMODULE_H
