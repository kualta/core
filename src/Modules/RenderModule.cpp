#include <core/Modules/RenderModule.h>
#include <bx/math.h>

namespace core {


void RenderModule::Update() {
    // TO BE MOVED TO CAMERA
    float view[16];
    float proj[16];
    const bx::Vec3 at = {0.0f, 0.0f,  0.0f};
    const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
    bx::mtxLookAt(view, eye, at);
    bx::mtxProj(proj, 60.0f, float(600) / float(400), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
    bgfx::setViewTransform(0, view, proj);
    // TO BE MOVED TO CAMERA

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