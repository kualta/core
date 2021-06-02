#include <core/Modules/BgfxRenderModule.h>

namespace core {

BgfxRenderModule::BgfxRenderModule()
: IRenderModule("Render", "bgfx") {

}
BgfxRenderModule::~BgfxRenderModule() {

}
void BgfxRenderModule::Frame() {
    bgfx::frame();
}

}