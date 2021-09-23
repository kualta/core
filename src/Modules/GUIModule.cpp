#include <core/Modules/GUIModule.h>
#include <core/Modules/ApplicationModule.h>
#include <core/GUIBehaviour.h>

namespace core {

GUIModule::GUIModule(ApplicationModule *appModule)
: IModule("GUI", WINDOW), appModule(appModule) {

}
void GUIModule::Start() {
    Vector2 dpiScale = appModule->GetWindowDpiScale(0);
    Vector2i windowSize = appModule->GetWindowSize(0);
    Vector2i frameBufferSize = appModule->GetFrameBufferSize(0);

    imgui = ImGuiIntegration::Context(Vector2(windowSize) / dpiScale, windowSize, frameBufferSize);
}
void GUIModule::EarlyTick() {
    imgui.newFrame();
}
void GUIModule::Tick() {
    UpdateGUI();
    DrawGUI();
}
void GUIModule::UpdateGUI() {
    std::for_each(GUIBehaviour::instances.begin(),
                  GUIBehaviour::instances.end(),
                  [&] (GUIBehaviour* b) { b->OnGUI(); });
}
void GUIModule::DrawGUI() {
    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::DepthTest);

    imgui.drawFrame();

    GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
}

}