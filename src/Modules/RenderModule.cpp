#include <core/Modules/RenderModule.h>
#include <bx/math.h>

namespace core {


void RenderModule::Tick() {

    bgfx::frame();
}
RenderModule::RenderModule() : IModule("Render", RENDER) {

}
RenderModule::~RenderModule() {

}


}