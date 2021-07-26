#include <core/Modules/BgfxRenderModule.h>
#include <core/Modules/BgfxWindowRenderer.h>

namespace core {

BgfxRenderModule::BgfxRenderModule(InputModule* inputModule)
: IRenderModule("Render", new BgfxWindowRenderer)
{

}
BgfxRenderModule::~BgfxRenderModule() {

}
void BgfxRenderModule::Frame() {
    bgfx::frame();
}

}