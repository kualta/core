#include <core/Modules/RenderModule.h>

namespace core {


void RenderModule::Update() {
    std::for_each(Renderer::instances.begin(), Renderer::instances.end(), [&](Renderer* renderer) {
        renderer->Draw();
    });
}
RenderModule::~RenderModule() {

}
RenderModule::RenderModule() : IModule("Render", RENDER) {

}


}