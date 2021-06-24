#include <core/Modules/BgfxRenderModule.h>
#include <core/BgfxWindowRenderer.h>

namespace core {

BgfxRenderModule::BgfxRenderModule()
: IRenderModule("Render",
                "bgfx",
                new BgfxWindowRenderer) {

}
BgfxRenderModule::~BgfxRenderModule() {

}
void BgfxRenderModule::Frame() {
    bgfx::frame();
}

}