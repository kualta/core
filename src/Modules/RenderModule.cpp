#include <core/Modules/RenderModule.h>
#include <bx/math.h>

namespace core {


void RenderModule::Tick() {

    std::for_each(Renderer::instances.begin(), Renderer::instances.end(), [&](Renderer* renderer) {
        renderer->Draw();
    });


    bgfx::frame();
}
RenderModule::RenderModule() : IModule("Render", RENDER) {

}
RenderModule::~RenderModule() {

}


}