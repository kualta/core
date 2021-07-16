#include <core/Modules/BgfxRenderModule.h>
#include <core/BgfxWindowRenderer.h>

namespace core {

BgfxRenderModule::BgfxRenderModule(InputModule* inputModule)
: IRenderModule("Render", new BgfxWindowRenderer, inputModule)
{

}
BgfxRenderModule::~BgfxRenderModule() {

}
void BgfxRenderModule::Frame() {
    bgfx::frame();
}

}